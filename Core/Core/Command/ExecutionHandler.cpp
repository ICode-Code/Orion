#include "ExecutionHandler.h"
#include "../Core/InfiniteVision/Renderers/2DTextureArrayExtractQuadRenderer/IV2DTextureArrayExtractQuadRenderer.h"
#include "../Core/InfiniteVision/Renderers/MaterialPreviewRenderer/IVMaterialPreviewRenderer.h"
#include "../GUI/Viewport/DynamicViewportManager/DynamicViewportManager.h"
#include "LogUI.h"

namespace OE1Core
{
	void ExecutionHandler::RegisterContentBrowserLayerNotifyCallback(const ContentBrowserLayerNotifyCallback& _callback)
	{
		s_ContentBrowserLayerNotifyCallback = _callback;
	}
	void ExecutionHandler::RegisterThreadInfoLayerNotifyCallback(const ThreadInfoLayerNotifyCallback& _callback)
	{
		s_ThreadInfoLayerNotifyCallback = _callback;
	}
	void ExecutionHandler::ProcessQueueCommands(Scene* _scene)
	{
		// Is anything that are loaded which need processing?
		ProcessAsset();

		// Any Material Creation Command?
		ProcessMaterialCreationCommand(_scene);

		// If there is anything to load?
		ProcessAssetLoadCommand();

		// Any Model Preview Command
		ProcessModelPreviewCommand();

		// Any Texture load request?
		ProcessTextureLoadCommand();

		// Any Texture Parsing request?
		ProcessTextureRawDataLoadCommand();

		// Any Material update request?
		ProcessMaterialTextureUpdateCommand();


		// Is any entity selection request?
		ProcessSelectionCommand();

		//Any MasterRenderer Material update request?
		ProcessMasterRendererMaterialRefershCommand(_scene);

		// Any Material Snapshot take command
		ProcessMaterialSnapshotCommand(_scene);

		// Any Viewport purge commands
		ProcessDynamicViewportPurgeCommand();

		// any Material Texture extraction command?
		ProcessMaterialTextureExtractionCommand();
	}
	void ExecutionHandler::ProcessMaterialTextureUpdateCommand()
	{
		while (!Command::s_MaterialTextureUpdateCommands.empty())
		{
			auto& command = Command::s_MaterialTextureUpdateCommands.front();

			// Note here since one of them only run on a call
			// It is okay to check and use the dirty flag after the swicth

			switch (command.TextureType)
			{
				case MaterialType::DIFFUSE:
					command.Material->RegisterAlbedoMap(command.NewTexture);
					break;
				case MaterialType::EMISSIVE:
					command.Material->RegisterEmissionMap(command.NewTexture);
					break;
				case MaterialType::NORMAL:
					command.Material->RegisterNormalMap(command.NewTexture);
					break;
				case MaterialType::METAL:
					command.Material->RegisterMetalMap(command.NewTexture);
					break;
				case MaterialType::METAL_ROUGHNESS:
					command.Material->RegisterMetalRoughnessMap(command.NewTexture);
					break;
				case MaterialType::ROUGHNESS:
					command.Material->RegisterRoughnessMap(command.NewTexture);
					break;
				case MaterialType::ALPHA:
					command.Material->RegisterAlphaMap(command.NewTexture);
					break;
				case MaterialType::AO:
					command.Material->RegisterAOMap(command.NewTexture);
					break;
				default:
					break;
			}

			if (command.Material->IsDirty())
			{
				MaterialType _mat_type_before_change = command.Material->m_Type;

				AvailTexture _flags(command.Material->m_TextureAvailFlag);
				command.Material->m_Type = _flags.GetMaterialType();
				std::string _new_frag_shader = ShaderGenerator::GetForwardPixelShader(_flags);
				command.Material->m_Shader->UpdateFragmentShader(_new_frag_shader);
				Memory::UniformBlockManager::LinkShader(command.Material->m_Shader);

				CommandDef::MasterRendererMaterialRefreshCommandDef commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));;

				commandX.Name = command.Material->m_Name;
				commandX.Offset = command.Material->m_Offset;
				commandX.Material = command.Material;

				Command::PushMasterRendererMaterialRefresh(commandX);
				command.Material->FlipDirtyFlag();
			}
			Renderer::IVMaterialPreviewRenderer::Refresh(command.Material, SceneManager::GetActiveScene());
			Command::s_MaterialTextureUpdateCommands.pop();
		}
	}
	void ExecutionHandler::ProcessMaterialTextureExtractionCommand()
	{
		while (!Command::s_MaterialTextureExtractionCommands.empty())
		{
			auto& command = Command::s_MaterialTextureExtractionCommands.front();

			MasterMaterial* master_material = command.Material;
			MaterialViewWin* material_view = command.MaterialView;
			//material_view->SetPrimaryMeshID(command.StaticMeshID);
			// Init Renderer 
			Renderer::IV2DTextureArrayExtractQuadRenderer* renderer = new Renderer::IV2DTextureArrayExtractQuadRenderer();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);


			// Make sure framebuffer is null since this call maybe intiate from the inside
			if (!material_view->m_Framebuffer)
				delete  material_view->m_Framebuffer;

			// Init Internal Framebuffer
			material_view->m_Framebuffer = new Renderer::IV2DTextureArrayExtractorFramebuffer(Renderer::IVFrameSize::R_640_480, FilterMaterialTexture(master_material));
			Renderer::CheckMatPreviewTexture has_texture = material_view->m_Framebuffer->GetCheckMaterialTextureX();
			
			material_view->m_Framebuffer->Attach();
			
			glViewport(0, 0, material_view->m_Framebuffer->GetWidth(), material_view->m_Framebuffer->GetHeight());
			
			renderer->GetShader()->Attach();
			
			renderer->GetShader()->Set1i("t_ColorMapTexture", 0);;
			renderer->GetShader()->Set1i("t_NoneColorMapTexture", 1);;

			renderer->GetShader()->Set1i("HasColor",			has_texture.HasColor);
			renderer->GetShader()->Set1i("HasNormal",			has_texture.HasNormal);
			renderer->GetShader()->Set1i("HasMetal",			has_texture.HasMetal);
			renderer->GetShader()->Set1i("HasRoughness",		has_texture.HasRoughness);
			renderer->GetShader()->Set1i("HasMetalRougness",	has_texture.HasMetalRougness);
			renderer->GetShader()->Set1i("HasEmission",			has_texture.HasEmission);
			renderer->GetShader()->Set1i("HasAlpha",			has_texture.HasAlpha);
			renderer->GetShader()->Set1i("HasAO",				has_texture.HasAO);
			renderer->GetShader()->Set1i("material_index",		master_material->GetOffset());

			master_material->Attach();

			renderer->RenderX();

			material_view->m_Framebuffer->Detach();


			delete renderer;
			Command::s_MaterialTextureExtractionCommands.pop();
			glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
		}
	}
	void ExecutionHandler::ProcessAssetLoadCommand()
	{
		while (!Command::s_Load3DAssetCommands.empty() && !s_3DAssetLoaderThread.IsRunning)
		{
			s_ThreadInfoLayerNotifyCallback(true);
			auto load_args = Command::s_Load3DAssetCommands.front();
			Command::s_Load3DAssetCommands.pop();
			s_3DAssetLoaderThread.Thread = std::thread(&Loader::GeometryLoader::LoadGeometry, load_args, std::ref(s_3DAssetLoaderThread.IsRunning));
			std::this_thread::sleep_for(0.5s);
			s_3DAssetLoaderThread.Thread.detach();
		}
	}
	void ExecutionHandler::ProcessAsset()
	{
		while (!Loader::GeometryLoader::s_MeshSets.empty())
		{
			auto& AssetPackage = Loader::GeometryLoader::s_MeshSets.front();
			std::vector<std::string> registered_packages = AssetParser::ParseStaticGeometry(AssetPackage.MeshSet, AssetPackage.TextureBuffer);
			Loader::LoadArgs& load_args = AssetPackage.Args;
			
			for (size_t i = 0; i < registered_packages.size(); i++)
			{
				std::string full_address = load_args.DestinationPath + "\\" + registered_packages[i] + ORI_ASSET_POSTFIX;
				std::ofstream file_macro(full_address, std::ios::out | std::ios::binary);
				ModelPkg* model = AssetManager::GetGeometry(registered_packages[i]);
				WriteBinary(file_macro, "-- ORION ENGINE ASSET -- \n\n\n");
				WriteBinary(file_macro, "Name:				" + model->Name + "\n");
				WriteBinary(file_macro, "Vertex Count:		" + std::to_string(model->VertexCount) + "\n");
				WriteBinary(file_macro, "Indices Count:		" + std::to_string(model->IndicesCount) + "\n");
				WriteBinary(file_macro, "Triangle Count:	" + std::to_string(model->TriangleCount) + "\n");
				WriteBinary(file_macro, "SubMesh Count:		" + std::to_string(model->SubMeshCount) + "\n\n");
				WriteBinary(file_macro, "--	--	--	--	\n");
				file_macro.close();

				CommandDef::ModelPreviewRenderCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
				command.Model = model;

				Command::PushModelPreviewRenderCommand(command);
			}
			
			Loader::GeometryLoader::s_MeshSets.pop();
			// update info
			s_ContentBrowserLayerNotifyCallback();
			LogLayer::Pipe("Asset Loaded " + load_args.SourcePath, OELog::INFO);
			Loader::StaticGeometryLoader::PROGRESS_INFO = "Finalizing Asset....";
		}

	}
	void ExecutionHandler::WriteBinary(std::ofstream& _file, std::string _data)
	{
		_file.write(_data.c_str(), _data.size());
	}

	void ExecutionHandler::ProcessSelectionCommand()
	{
		if (!Command::s_EntitySelectionCommands.empty())
		{
			CommandDef::EntitySelectionCommandDef& _command = Command::s_EntitySelectionCommands.back();
			Scene* active_scene = SceneManager::GetActiveScene();
			uint32_t entity_id = static_cast<uint32_t>(active_scene->m_MasterCamera->GetMainPassFramebuffer()->Readi1(1, _command.posX, _command.posY));
			
			Entity entity_query = SceneManager::GetActiveScene()->GetEntity(entity_id, true);

			if (entity_query.IsFunctional())
			{
				if (_command.Batch)
				{
					active_scene->GetActiveEntity()->PickBatch(entity_query);
				}
				else
				{
					active_scene->GetActiveEntity()->Pick(entity_query);
				}
			}
			else
				active_scene->GetActiveEntity()->FlushSelection();
			
			Command::s_EntitySelectionCommands.pop();
		}
	}
	Renderer::CheckMatPreviewTexture ExecutionHandler::FilterMaterialTexture(MasterMaterial* _material)
	{
		Renderer::CheckMatPreviewTexture data;

		Memory::TextureAccessIndex texture_idx = _material->GetTAI();

		if (texture_idx.Color != -1)
			data.HasColor = true;

		if (texture_idx.Emission != -1)
			data.HasEmission = true;

		if (texture_idx.Normal != -1)
			data.HasNormal = true;

		if (texture_idx.Roughness != -1)
			data.HasRoughness = true;

		if (texture_idx.Metal != -1)
			data.HasMetal = true;

		if (texture_idx.RoughnessMetal != -1)
			data.HasMetalRougness = true;

		if (texture_idx.AmbientOcclusion != -1)
			data.HasAO = true;

		if (texture_idx.AlphaMask != -1)
			data.HasAlpha = true;

		return data;

	}

	void ExecutionHandler::ProcessTextureLoadCommand()
	{
		while (!Command::s_TextureLoadCommands.empty())
		{
			auto& command = Command::s_TextureLoadCommands.front();
			std::string full_address = command.Destination + "\\" + command.Name + ORI_TEXTURE_POSTFIX;
			AssetManager::RegisterTexture(command.Path, command.Name);
			Texture* _texture = AssetManager::GetTexture(command.Name);

			std::ofstream file_texture(full_address, std::ios::out | std::ios::binary);
			WriteBinary(file_texture, "-- ORION ENGINE TEXTURE -- \n\n\n");
			WriteBinary(file_texture, "Name:				" + command.Name + "\n");
			WriteBinary(file_texture, "Dest:		" + command.Destination + "\n");
			std::string res_value = "[" + std::to_string(_texture->GetWidth()) + " X " + std::to_string(_texture->GetWidth()) + "]";
			WriteBinary(file_texture, "Resolution:		" + res_value + "\n");
			WriteBinary(file_texture, "--	--	--	--	\n");
			file_texture.close();

			LogLayer::Pipe("Texture Loaded " + command.Name, OELog::INFO);
			Command::s_TextureLoadCommands.pop();
			s_ContentBrowserLayerNotifyCallback();
		}
	}
	void ExecutionHandler::ProcessTextureRawDataLoadCommand()
	{
		while (!Command::s_TextureLoadRawDataCommands.empty())
		{
			auto& command = Command::s_TextureLoadRawDataCommands.front();
			std::string full_address = ORI_PROJECT_HOT_DIRECTORY + "\\" + command.Name + ORI_TEXTURE_POSTFIX;

			std::ofstream file_texture(full_address, std::ios::out | std::ios::binary);
			WriteBinary(file_texture, "-- ORION ENGINE TEXTURE -- \n\n\n");
			WriteBinary(file_texture, "Name:				" + command.Name + "\n");
			WriteBinary(file_texture, "Dest:		" + ORI_PROJECT_HOT_DIRECTORY + "\n");
			std::string res_value = "[" + std::to_string(command.Width) + " X " + std::to_string(command.Height) + "]";
			WriteBinary(file_texture, "Resolution:		" + res_value + "\n");
			WriteBinary(file_texture, "--	--	--	--	\n");
			file_texture.close();

			AssetManager::RegisterTexture(command);

			Command::s_TextureLoadRawDataCommands.pop();
			s_ContentBrowserLayerNotifyCallback();
		}
	}
	void ExecutionHandler::ProcessMasterRendererMaterialRefershCommand(Scene* _scene)
	{
		while (!Command::s_MasterRendererMaterialRefreshCommands.empty())
		{
			auto& commandX = Command::s_MasterRendererMaterialRefreshCommands.front();

			// Process
			_scene->GetRenderer()->ReEvaluateRenderStackMaterial(commandX.Material);

			Command::s_MasterRendererMaterialRefreshCommands.pop();
		}
	}
	void ExecutionHandler::ProcessDynamicViewportPurgeCommand()
	{
		while (!Command::s_DyanmicViewportPurgeCommands.empty())
		{
			auto& commandX = Command::s_DyanmicViewportPurgeCommands.front();
			DynamicViewportManager::PurgeDynamicViewport(commandX.Name);
			Command::s_DyanmicViewportPurgeCommands.pop();
		}
	}

	void ExecutionHandler::ProcessMaterialSnapshotCommand(Scene* _scene)
	{
		while (!Command::s_MaterialSnapshotCommands.empty())
		{
			auto& commandX = Command::s_MaterialSnapshotCommands.front();

			std::string full_address = ORI_PROJECT_HOT_DIRECTORY + "\\"  + commandX.Name + ORI_MATERIAL_POSTFIX;

			std::ofstream file_texture(full_address, std::ios::out | std::ios::binary);
			WriteBinary(file_texture, "-- ORION ENGINE MATERIAL -- \n\n\n");
			WriteBinary(file_texture, "Name:				" + commandX.Name + "\n");
			WriteBinary(file_texture, "Dest:		" + ORI_PROJECT_HOT_DIRECTORY + "\n");
			WriteBinary(file_texture, "--	--	--	--	\n");
			file_texture.close();


			// Render Preivew
			Renderer::IVMaterialPreviewRenderer::Render(commandX.Material, _scene);
			

			Command::s_MaterialSnapshotCommands.pop();
			s_ContentBrowserLayerNotifyCallback();
		}
	}
	void ExecutionHandler::ProcessMaterialCreationCommand(Scene* _scene)
	{
		while (!Command::s_MaterialCreationCommands.empty())
		{
			auto& commandX = Command::s_MaterialCreationCommands.front();

			// Query Targte Mesh
			ModelPkg* TARGET_MESH = AssetManager::GetGeometry(commandX.TargetMeshID);
			// Check if the same material exist
			MasterMaterial* _mat = MaterialManager::GetMaterial(commandX.MaterialName);
			if (_mat)
			{
				AssignMaterial(TARGET_MESH, _mat, commandX.LocalSubMeshID);
			}
			else
			{

				bool same_material_found = false;
				if (commandX.TextureFlag.HasColor)
				{
					MasterMaterial* _same_Master_material = nullptr;
					Texture* query_texture = AssetManager::GetTexture(commandX.Textuers[DataBlock::TextureType::DIFFUSE].Name);
					if (query_texture)
					{
						auto& associate_material_offset = query_texture->AssociateMaterialOffset();
						for (size_t i = 0; associate_material_offset.size(); i++)
						{
							_same_Master_material = MaterialManager::GetMaterial(associate_material_offset[i]);
							if (_same_Master_material)
								break;
						}

						if (_same_Master_material)
						{
							same_material_found = true;
							AssignMaterial(TARGET_MESH, _same_Master_material, commandX.LocalSubMeshID);
						}
					}
					 
				}

				if (!same_material_found)
				{
					// Identify material type
					MaterialType MATERIAL_TYPE = commandX.AvialTextures.GetMaterialType();

					// Prepare shader based on the material type
					std::string VERTEX_SHADER = ShaderGenerator::GetStandardVertexShader();
					std::string VERTEX_SHADER_PROXY = ShaderGenerator::GetStandardProxyVertexShader();
					std::string FRAGMENT_SHADER = ShaderGenerator::GetForwardPixelShader(commandX.AvialTextures);


					// Create Master Material
					MasterMaterial* MASTER_MATERIAL = MaterialManager::RegisterMaterial(
						commandX.MaterialName, new Shader(VERTEX_SHADER.c_str(), FRAGMENT_SHADER.c_str(), VERTEX_SHADER_PROXY.c_str())
					);


					if (MATERIAL_TYPE == MaterialType::DEFAULT)
					{
						MASTER_MATERIAL->Update();
						AssignMaterial(TARGET_MESH, MASTER_MATERIAL, commandX.LocalSubMeshID);

						CommandDef::MaterialSnapShotCommandDefs _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));;
						_command.Material = MASTER_MATERIAL;
						_command.Name = MASTER_MATERIAL->GetName();
						_command.Offset = MASTER_MATERIAL->GetOffset();
						Command::PushMaterialSnapshotCommand(_command);


					}
					else
					{
						if (commandX.TextureFlag.HasColor)
							MASTER_MATERIAL->RegisterAlbedoMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::DIFFUSE]));

						if (commandX.TextureFlag.HasNormal)
							MASTER_MATERIAL->RegisterNormalMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::NORMAL]));

						if (commandX.TextureFlag.HasMetalRoughness)
							MASTER_MATERIAL->RegisterMetalRoughnessMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::METAL_ROUGHNESS]));
						else
						{
							if (commandX.TextureFlag.HasRoughness)
								MASTER_MATERIAL->RegisterRoughnessMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::ROUGHNESS]));

							if (commandX.TextureFlag.HasMetal)
								MASTER_MATERIAL->RegisterMetalMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::METAL]));

						}

						if (commandX.TextureFlag.HasAO)
							MASTER_MATERIAL->RegisterAOMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::AO]));

						if (commandX.TextureFlag.HasEmission)
							MASTER_MATERIAL->RegisterEmissionMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::EMISSIVE]));

						if (commandX.TextureFlag.HasAlpha)
							MASTER_MATERIAL->RegisterAlphaMap(AssetManager::RegisterTexture(commandX.Textuers[DataBlock::TextureType::OPACITY]));

						MASTER_MATERIAL->Update();
						AssignMaterial(TARGET_MESH, MASTER_MATERIAL, commandX.LocalSubMeshID);

						CommandDef::MaterialSnapShotCommandDefs _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));;
						_command.Material = MASTER_MATERIAL;
						_command.Name = MASTER_MATERIAL->GetName();
						_command.Offset = MASTER_MATERIAL->GetOffset();
						Command::PushMaterialSnapshotCommand(_command);
					}
				}
			
			}

			Command::s_MaterialCreationCommands.pop();

			Loader::StaticGeometryLoader::PROGRESS_INFO = "Creating Material....";
			s_ThreadInfoLayerNotifyCallback(false);
		}
	}
	void ExecutionHandler::ProcessModelPreviewCommand()
	{
		while (!Command::s_ModelPreviewRenderCommands.empty())
		{
			auto& commandX = Command::s_ModelPreviewRenderCommands.front();

			Renderer::IVModelPreviewRenderer::Render(*commandX.Model);

			Command::s_ModelPreviewRenderCommands.pop();
			
		}
	}
	bool ExecutionHandler::AssignMaterial(ModelPkg* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id)
	{
		bool _positive_return = false;
		for (size_t i = 0; i < _mesh->MeshList.size(); i++)
		{
			if (_mesh->MeshList[i].LocalID == _sub_mesh_id)
			{
				_mesh->MeshList[i].Material = _material;
				_mesh->MeshList[i].MaterialID = _material->GetOffset();
				_positive_return = true;
				break;
			}
		}

		return _positive_return;
	}
}
