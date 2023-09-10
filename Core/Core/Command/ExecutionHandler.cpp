#include "ExecutionHandler.h"


namespace OE1Core
{
	void ExecutionHandler::ProcessQueueCommands()
	{
		ProcessAssetLoadCommand();
		ProcessAsset();


		
	}

	void ExecutionHandler::ProcessAssetLoadCommand()
	{
		while (!Command::s_Load3DAssetCommands.empty() && !s_3DAssetLoaderThread.IsRunning)
		{
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
			AssetParser::ParseStaticGeometry(std::get<1>(mesh_data));
			Loader::LoadArgs& load_args = std::get<0>(mesh_data);
			
			Loader::GeometryLoader::s_MeshSets.pop();

			// update info
			Loader::StaticGeometryLoader::PROGRESS_INFO = "Job Done.";
			
		}
	}
}