#include "ExecutionHandler.h"
#include "../Core/InfiniteVision/Renderers/2DTextureArrayExtractQuadRenderer/IV2DTextureArrayExtractQuadRenderer.h"

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
	void ExecutionHandler::ProcessQueueCommands()
	{
		ProcessAssetLoadCommand();
		ProcessAsset();

		ProcessSelectionCommand();
		ProcessMaterialTextureExtractionCommand();
	}
	void ExecutionHandler::ProcessMaterialTextureExtractionCommand()
	{
		while (!Command::s_MaterialTextureExtractionCommands.empty())
		{
			auto& command = Command::s_MaterialTextureExtractionCommands.front();

			MasterMaterial* master_material = command.Material;
			MaterialViewWin* material_view = command.MaterialView;

			// Init Renderer 
			Renderer::IV2DTextureArrayExtractQuadRenderer* renderer = new Renderer::IV2DTextureArrayExtractQuadRenderer();

			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			// Init Internal Framebuffer
			material_view->m_Framebuffer = new Renderer::IV2DTextureArrayExtractorFramebuffer(Renderer::IVFrameSize::R_640_480, FilterMaterialTexture(master_material));
			Renderer::CheckMatPreviewTexture has_texture = material_view->m_Framebuffer->GetCheckMaterialTextureX();
			
			material_view->m_Framebuffer->Attach();
			
			glViewport(0, 0, material_view->m_Framebuffer->GetWidth(), material_view->m_Framebuffer->GetHeight());
			
			renderer->GetShader()->Attach();
			
			renderer->GetShader()->set1i("t_ColorMapTexture", 0);;
			renderer->GetShader()->set1i("t_NoneColorMapTexture", 1);;

			renderer->GetShader()->set1i("HasColor",			has_texture.HasColor);
			renderer->GetShader()->set1i("HasNormal",			has_texture.HasNormal);
			renderer->GetShader()->set1i("HasMetal",			has_texture.HasMetal);
			renderer->GetShader()->set1i("HasRoughness",		has_texture.HasRoughness);
			renderer->GetShader()->set1i("HasMetalRougness",	has_texture.HasMetalRougness);
			renderer->GetShader()->set1i("HasEmission",			has_texture.HasEmission);
			renderer->GetShader()->set1i("HasAlpha",			has_texture.HasAlpha);
			renderer->GetShader()->set1i("HasAO",				has_texture.HasAO);
			renderer->GetShader()->set1i("material_index",		master_material->GetOffset());

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
			auto& mesh_data = Loader::GeometryLoader::s_MeshSets.front();
			std::vector<std::string> registered_packages = AssetParser::ParseStaticGeometry(std::get<1>(mesh_data));
			Loader::LoadArgs& load_args = std::get<0>(mesh_data);
			
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

				Renderer::IVModelPreviewRenderer::Render(*model);
			}
			
			Loader::GeometryLoader::s_MeshSets.pop();
			// update info
			s_ContentBrowserLayerNotifyCallback();
			Loader::StaticGeometryLoader::PROGRESS_INFO = "Job Done.";
			s_ThreadInfoLayerNotifyCallback(false);
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
			uint32_t entity_id = static_cast<uint32_t>(active_scene->GetRenderer()->GetMainPassFramebuffer().Readi1(1, _command.posX, _command.posY));
			
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
}