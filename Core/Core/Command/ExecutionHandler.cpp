#include "ExecutionHandler.h"
#include <iostream>

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
			uint32_t entity_id = static_cast<uint32_t>(SceneManager::GetActiveScene()->GetRenderer()->GetMainPassFramebuffer().Readi1(1, _command.posX, _command.posY));
			
			Entity entity_query = SceneManager::GetActiveScene()->GetEntity(entity_id, false);

			if (entity_query.IsFunctional())
				ActiveEntity::Pick(entity_query);
			else
				ActiveEntity::FlushSelection();
			
			Command::s_EntitySelectionCommands.pop();
		}
	}
}