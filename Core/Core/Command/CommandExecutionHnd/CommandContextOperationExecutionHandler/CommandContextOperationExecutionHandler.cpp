#include "CommandContextOperationExecutionHandler.h"
#include "LogUI.h"


#include "../GUI/Viewport/DynamicViewportManager/DynamicViewportManager.h"
#include "../Core/InfiniteVision/Renderers/2DTextureArrayExtractQuadRenderer/IV2DTextureArrayExtractQuadRenderer.h"

#include "../Core/DS/DebugOTInit/DebugOTInit.h"

#include "AnimationLoader/AnimationLoader.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		CommandContextOperationExeHandler::CommandContextOperationExeHandler(Scene* _scene)
			: ExecutionHandleBase{ _scene }
		{

		}

		CommandContextOperationExeHandler::~CommandContextOperationExeHandler()
		{
			 
		}

		void CommandContextOperationExeHandler::ProcessQueue()
		{
			ProcessOnViewportClickReadbackCommand();


			// Texture Load Command
			ProcessTextureLoadCommand();
			ProcessRawDataTextureLoadCommand();

			// Material Update
			//ProcessMaterialCreationCommand();
			ProcessMasterMaterialUpdateCommand();
			ProcessMaterialReEvaluationCommand();
			ProcessMaterialTextureExtractionForPReviewCommand();

			ProcessParseLoadedAssetCommand();

			ProcessParseLoadedDynamicMeshCommand();

			ProcessAnimationLoadCommand();
			ProcessAnimationSwitchCommand();

			ProcessMaterialPreviewRenderCommand();

			ProcessModelPreviewRenderCommand();
			ProcessDynamicMeshPreivewRendererCommand();
			ProcessSceneDebugShapeCreateCommand();
			ProcessSceneDebugShapeUpdateCommand();
		}


		/// Process
		void CommandContextOperationExeHandler::ProcessMaterialTextureExtractionForPReviewCommand()
		{
			while (!Command::s_MaterialTextureExtractionCommands.empty())
			{
				auto& command = Command::s_MaterialTextureExtractionCommands.front();

				MasterMaterial* master_material = command.Material;
				MaterialViewWin* material_view = command.MaterialView;
				//material_view->SetPrimaryMeshID(command.StaticMeshID);
				// Init Renderer 
				Renderer::IV2DTextureArrayExtractQuadRenderer* renderer = new Renderer::IV2DTextureArrayExtractQuadRenderer();

				// Make sure framebuffer is null since this call maybe intiate from the inside
				if (!material_view->m_Framebuffer)
					delete  material_view->m_Framebuffer;

				// Init Internal Framebuffer
				material_view->m_Framebuffer = new Renderer::IV2DTextureArrayExtractorFramebuffer(Renderer::IVFrameSize::R_640_480, FilterMaterialTexture(master_material));
				Renderer::CheckMatPreviewTexture has_texture = material_view->m_Framebuffer->GetCheckMaterialTextureX();

				material_view->m_Framebuffer->Attach();

				renderer->GetShader()->Attach();

				renderer->GetShader()->Set1i("t_ColorMapTexture", 0);;
				renderer->GetShader()->Set1i("t_NoneColorMapTexture", 1);;

				renderer->GetShader()->Set1i("HasColor", has_texture.HasColor);
				renderer->GetShader()->Set1i("HasNormal", has_texture.HasNormal);
				renderer->GetShader()->Set1i("HasMetal", has_texture.HasMetal);
				renderer->GetShader()->Set1i("HasRoughness", has_texture.HasRoughness);
				renderer->GetShader()->Set1i("HasMetalRougness", has_texture.HasMetalRougness);
				renderer->GetShader()->Set1i("HasEmission", has_texture.HasEmission);
				renderer->GetShader()->Set1i("HasAlpha", has_texture.HasAlpha);
				renderer->GetShader()->Set1i("HasAO", has_texture.HasAO);
				renderer->GetShader()->Set1i("material_index", master_material->GetOffset());

				master_material->Attach();

				renderer->RenderX();

				material_view->m_Framebuffer->Detach();


				delete renderer;
				Command::s_MaterialTextureExtractionCommands.pop();
			}
		}
		void CommandContextOperationExeHandler::ProcessMaterialReEvaluationCommand()
		{
			while (!Command::s_MasterRendererMaterialRefreshCommands.empty())
			{
				auto& commandX = Command::s_MasterRendererMaterialRefreshCommands.front();

				// Process
				m_Scene->GetRenderer()->ReEvaluateRenderStackMaterial(commandX.Material);

				Command::s_MasterRendererMaterialRefreshCommands.pop();
			}
		}
		void CommandContextOperationExeHandler::ProcessMaterialCreationCommand()
		{
			
		}

		void CommandContextOperationExeHandler::ProcessAnimationSwitchCommand()
		{
			while (!Command::s_AnimationSwitchCommands.empty())
			{
				auto& command = Command::s_AnimationSwitchCommands.front();

				Entity _entity = m_Scene->GetEntity(command.EntityID);

				_entity.GetComponent<Component::AnimationComponent>().SetAnimation(command.TargetAnimation);


				Command::s_AnimationSwitchCommands.pop();
			}
		}
		void CommandContextOperationExeHandler::ProcessMasterMaterialUpdateCommand()
		{
			while (!Command::s_MaterialTextureUpdateCommands.empty())
			{
				auto& command = Command::s_MaterialTextureUpdateCommands.front();

				// Note here since one of them only run on a call
				// It is okay to check and use the dirty flag after the switch

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

					CommandDef::MasterRendererMaterialRefreshCommandDef commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));

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
		void CommandContextOperationExeHandler::ProcessRawDataTextureLoadCommand()
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
				
				LogLayer::Pipe(" Texture Loaded  [" + command.Name + " ] ", OELog::INFO);

				Command::s_TextureLoadRawDataCommands.pop();
				Command::s_ContentBrowserLayerNotifyCallback();
			}
		}
		void CommandContextOperationExeHandler::ProcessTextureLoadCommand()
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

				LogLayer::Pipe(" Texture Loaded  [" + command.Name + " ] ", OELog::INFO);
				Command::s_TextureLoadCommands.pop();
				Command::s_ContentBrowserLayerNotifyCallback();
			}
		}
		void CommandContextOperationExeHandler::ProcessModelPreviewRenderCommand()
		{
			const size_t command_count = Command::s_ModelPreviewRenderCommands.size();
			size_t visited_commnad = 0;
			while (!Command::s_ModelPreviewRenderCommands.empty())
			{
				visited_commnad++;
				auto& commandX = Command::s_ModelPreviewRenderCommands.front();

				if (!commandX.Lock)
				{
					if (visited_commnad >= command_count)
						break;
					continue;
				}

				Renderer::IVModelPreviewRenderer::Render(*commandX.Model);

				Command::s_ModelPreviewRenderCommands.pop();

				if(Command::s_ModelPreviewRenderCommands.empty())
					Command::s_ThreadInfoLayerNotifyCallback(false);
			}
		}
		void CommandContextOperationExeHandler::ProcessDynamicMeshPreivewRendererCommand()
		{
			const size_t command_count = Command::s_DynamicMeshModelPreviewRenderCommands.size();
			size_t visited_commnad = 0;
			while (!Command::s_DynamicMeshModelPreviewRenderCommands.empty())
			{
				visited_commnad++;
				auto& commandX = Command::s_DynamicMeshModelPreviewRenderCommands.front();

				if (!commandX.Lock)
				{
					if (visited_commnad >= command_count)
						break;
					continue;
				}

				Renderer::IVModelPreviewRenderer::Render(*commandX.Model);

				Command::s_DynamicMeshModelPreviewRenderCommands.pop();

				if (Command::s_DynamicMeshModelPreviewRenderCommands.empty())
					Command::s_ThreadInfoLayerNotifyCallback(false);
			}
		}
		void CommandContextOperationExeHandler::ProcessMaterialPreviewRenderCommand()
		{
			const size_t command_count = Command::s_MaterialSnapshotCommands.size();
			size_t visited_commnad = 0;
			while (!Command::s_MaterialSnapshotCommands.empty())
			{
				auto& commandX = Command::s_MaterialSnapshotCommands.front();

				if (!commandX.Lock)
				{
					if (visited_commnad >= command_count)
						break;
					continue;
				}

				std::string full_address = ORI_PROJECT_HOT_DIRECTORY + "\\" + commandX.Name + ORI_MATERIAL_POSTFIX;

				std::ofstream file_texture(full_address, std::ios::out | std::ios::binary);
				WriteBinary(file_texture, "-- ORION ENGINE MATERIAL -- \n\n\n");
				WriteBinary(file_texture, "Name:				" + commandX.Name + "\n");
				WriteBinary(file_texture, "Dest:		" + ORI_PROJECT_HOT_DIRECTORY + "\n");
				WriteBinary(file_texture, "--	--	--	--	\n");
				file_texture.close();


				// Render Preivew
				Renderer::IVMaterialPreviewRenderer::Render(commandX.Material, m_Scene);


				Command::s_MaterialSnapshotCommands.pop();
				Command::s_ContentBrowserLayerNotifyCallback();
			}
		}
		void CommandContextOperationExeHandler::ProcessParseLoadedAssetCommand()
		{
			// Iterate until all mesh sets are processed
			while (!Loader::IVLoadedAsset::s_StaticMeshAsset.empty())
			{
				// Retrieve the next mesh set to process
				auto& AssetPackage = Loader::IVLoadedAsset::s_StaticMeshAsset.front();

				// Parse geometry data and get registered packages
				std::vector<std::string> registered_packages = AssetParser::ParseStaticGeometry(AssetPackage.StaticMeshSet);

				// Retrieve load arguments for the current asset package
				Loader::LoadArgs& load_args = AssetPackage.LoadArg;

				// Process each registered package
				for (size_t i = 0; i < registered_packages.size(); i++)
				{
					// Construct the full address for the asset file
					std::string full_address = load_args.DestinationPath + "\\" + registered_packages[i] + ORI_STATIC_MESH_ASSET_POSTFIX;

					// Open the file for writing in binary mode
					std::ofstream file_macro(full_address, std::ios::out | std::ios::binary);

					// Retrieve model data from asset manager
					IVModel* model = AssetManager::GetGeometry(registered_packages[i]);

					// Write metadata to the file
					WriteBinary(file_macro, "-- ORION ENGINE ASSET -- \n\n\n");
					WriteBinary(file_macro, "Name:				" + model->Name + "\n");
					WriteBinary(file_macro, "Type:				STATIC\n");
					WriteBinary(file_macro, "Vertex Count:		" + std::to_string(model->TotalVertexCount) + "\n");
					WriteBinary(file_macro, "Indices Count:		" + std::to_string(model->TotalIndicesCount) + "\n");
					WriteBinary(file_macro, "Triangle Count:	" + std::to_string(model->TotalTriangleCount) + "\n");
					WriteBinary(file_macro, "SubMesh Count:		" + std::to_string(model->SubMeshCount) + "\n\n");
					WriteBinary(file_macro, "--	--	--	--	\n");

					// Close the file
					file_macro.close();

					// Create and push model preview render command
					CommandDef::ModelPreviewRenderCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
					command.Model = model;
					Command::PushModelPreviewRenderCommand(command);
				}

				// Remove the processed mesh set from the queue
				Loader::IVLoadedAsset::s_StaticMeshAsset.pop();

				// Update information
				Command::s_ContentBrowserLayerNotifyCallback();
				LogLayer::Pipe("Asset Loaded " + load_args.SourcePath, OELog::INFO);
				Loader::CoreGeometryLoader::PROGRESS_INFO = "Finalizing Asset....";

				// If all mesh sets are processed, lock material creation commands
				if (Loader::IVLoadedAsset::s_StaticMeshAsset.empty())
					Command::LockCommand<CommandDef::MaterialCreationCommandDef>(Command::s_MaterialCreationCommands);
			}
		}
		void CommandContextOperationExeHandler::ProcessParseLoadedDynamicMeshCommand()
		{
			// Iterate until all mesh sets are processed
			while (!Loader::IVLoadedAsset::s_SkinnedMeshAsset.empty())
			{
				// Retrieve the next mesh set to process
				auto& AssetPackage = Loader::IVLoadedAsset::s_SkinnedMeshAsset.front();

				// Parse geometry data and get registered packages
				std::vector<std::string> registered_packages = AssetParser::ParseDynamicGeometry(AssetPackage.SkinnedMeshSet);

				// Retrieve load arguments for the current asset package
				Loader::LoadArgs& load_args = AssetPackage.LoadArg;

				// Process each registered package
				for (size_t i = 0; i < registered_packages.size(); i++)
				{
					// Construct the full address for the asset file
					std::string full_address = load_args.DestinationPath + "\\" + registered_packages[i] + ORI_DYNAMIC_MESH_ASSET_POSTFIX;

					// Open the file for writing in binary mode
					std::ofstream file_macro(full_address, std::ios::out | std::ios::binary);

					// Retrieve model data from asset manager
					IVModel* model = AssetManager::GetGeometry(registered_packages[i]);
					auto animations = Loader::AnimationLoader::LoadAnimation(load_args.SourcePath, AssetPackage.BoneInfoMap);
					AssetManager::RegisterAnimation(animations);
					model->DataIdx = GeometryPacket::GeometryAssetPacketBuffer::RegisterSkinnedIVModelCustomData(
						AssetPackage.BoneInfoMap,
						animations);

					// Write metadata to the file
					WriteBinary(file_macro, "-- ORION ENGINE ASSET -- \n\n\n");
					WriteBinary(file_macro, "Name:				" + model->Name + "\n");
					WriteBinary(file_macro, "Type:				DYNAMIC\n");
					WriteBinary(file_macro, "Vertex Count:		" + std::to_string(model->TotalVertexCount) + "\n");
					WriteBinary(file_macro, "Indices Count:		" + std::to_string(model->TotalIndicesCount) + "\n");
					WriteBinary(file_macro, "Triangle Count:	" + std::to_string(model->TotalTriangleCount) + "\n");
					WriteBinary(file_macro, "SubMesh Count:		" + std::to_string(model->SubMeshCount) + "\n\n");
					WriteBinary(file_macro, "--	--	--	--	\n");

					// Close the file
					file_macro.close();

					// Create and push model preview render command
					CommandDef::DynamicMeshModelPreviewRenderCommandDef command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
					command.Model = model;
					Command::PushDynamicMeshModelPreviewRenderCommand(command);
				}

				// Remove the processed mesh set from the queue
				Loader::IVLoadedAsset::s_SkinnedMeshAsset.pop();

				// Update information
				Command::s_ContentBrowserLayerNotifyCallback();
				LogLayer::Pipe("Asset Loaded " + load_args.SourcePath, OELog::INFO);
				Loader::CoreGeometryLoader::PROGRESS_INFO = "Finalizing Asset....";

				// If all mesh sets are processed, lock material creation commands
				if (Loader::IVLoadedAsset::s_SkinnedMeshAsset.empty())
					Command::LockCommand<CommandDef::MaterialCreationCommandDef>(Command::s_MaterialCreationCommands);
			}
		}
		void CommandContextOperationExeHandler::ProcessAnimationLoadCommand()
		{
			while (!Command::s_AnimationLoadCommands.empty())
			{
				auto& commandX = Command::s_AnimationLoadCommands.front();

				IVModel* model = AssetManager::GetGeometry(commandX.PackageID);
				auto _data = GeometryPacket::GeometryAssetPacketBuffer::GetSkinnedIVModelCustomData(model->DataIdx);
				
				auto animations = Loader::AnimationLoader::LoadAnimation(commandX.Path, _data->BoneInfoMap);
				
				AssetManager::RegisterAnimation(animations);

				GeometryPacket::GeometryAssetPacketBuffer::UpdateSkinnedIVModelCustomData(model->DataIdx, _data->BoneInfoMap, animations);

				m_Scene->QueryDynamicMesh(commandX.PackageID)->UpdateData(GeometryPacket::GeometryAssetPacketBuffer::GetSkinnedIVModelCustomData(model->DataIdx));

				Command::s_AnimationLoadCommands.pop();
			}
		}
		void CommandContextOperationExeHandler::ProcessOnViewportClickReadbackCommand()
		{
			while (!Command::s_EntitySelectionCommands.empty())
			{
				CommandDef::EntitySelectionCommandDef& _command = Command::s_EntitySelectionCommands.back();

				uint32_t entity_id = static_cast<uint32_t>(m_Scene->m_MasterCamera->GetMainPassFramebuffer()->Readi1(1, _command.posX, _command.posY));

				Entity entity_query = SceneManager::GetActiveScene()->GetEntity(entity_id, true);

				if (entity_query.IsFunctional())
				{
					if (_command.Batch)
					{
						m_Scene->GetActiveEntity()->PickBatch(entity_query);
					}
					else
					{
						m_Scene->GetActiveEntity()->Pick(entity_query);
					}
				}
				else
					m_Scene->GetActiveEntity()->FlushSelection();

				Command::s_EntitySelectionCommands.pop();
			}
		}
		Renderer::CheckMatPreviewTexture CommandContextOperationExeHandler::FilterMaterialTexture(MasterMaterial* _material)
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
		bool CommandContextOperationExeHandler::AssignMaterial(IVModel* _mesh, MasterMaterial* _material, uint32_t _sub_mesh_id)
		{
			bool _positive_return = false;
			for (size_t i = 0; i < _mesh->SubMeshs.size(); i++)
			{
				if (_mesh->SubMeshs[i].LocalMeshID == _sub_mesh_id)
				{
					_mesh->SubMeshs[i].Material = _material;
					_mesh->SubMeshs[i].MaterialID = _material->GetOffset();
					_positive_return = true;
					break;
				}
			}

			return _positive_return;
		}
		void CommandContextOperationExeHandler::ProcessSceneDebugShapeCreateCommand()
		{
			while (!Command::s_SceneDebugShapeCreateCommands.empty())
			{
				auto& commandX = Command::s_SceneDebugShapeCreateCommands.front();

				DS::DebugOTInit::Init(*commandX.Node);

				Command::s_SceneDebugShapeCreateCommands.pop();
			}
		}
		void CommandContextOperationExeHandler::ProcessSceneDebugShapeUpdateCommand()
		{
			while (!Command::s_SceneDebugShapeUpdateCommands.empty())
			{
				auto& commandX = Command::s_SceneDebugShapeUpdateCommands.front();

				DS::DebugOTInit::Update(*commandX.Node);

				Command::s_SceneDebugShapeUpdateCommands.pop();
			}
		}
	}
}