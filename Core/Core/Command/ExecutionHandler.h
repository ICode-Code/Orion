#ifndef OE1_EXECUTION_HANDLER_H_
#define OE1_EXECUTION_HANDLER_H_

#include "Util/LoadArgs.h"
#include "Geometry/GeometryLoader.h"
#include "../../AssetManager/AssetParser/AssetParser.h"
#include "../InfiniteVision/Renderers/ModelPreviewRenderer/IVModelPreviewRenderer.h"
#include "../InfiniteVision/IVMasterRenderer.h"
#include "../Scene/SceneManager.h"
#include "Commnad.h"

#include <functional>
#include <fstream>
#include <thread>
#include <Log.h>


using namespace std::chrono_literals;

namespace OE1Core
{
	struct _3DAssetLoaderThreadPkg
	{
		std::thread Thread;
		bool IsRunning = false;
	};

	
	typedef std::function<void()> ContentBrowserLayerNotifyCallback;
	typedef std::function<void(bool)> ThreadInfoLayerNotifyCallback;

	class ExecutionHandler
	{
	public:
		static void ProcessQueueCommands();
		static void RegisterContentBrowserLayerNotifyCallback(const ContentBrowserLayerNotifyCallback& _callback);
		static void RegisterThreadInfoLayerNotifyCallback(const ThreadInfoLayerNotifyCallback& _callback);

	protected:
		static void ProcessSelectionCommand();
		static void ProcessAssetLoadCommand();
		static void ProcessTextureLoadCommand();
		static void ProcessMaterialTextureExtractionCommand();
		static void ProcessAsset();
		static void WriteBinary(std::ofstream& _file, std::string _data);
		static Renderer::CheckMatPreviewTexture FilterMaterialTexture(MasterMaterial* _material);
		


	private:
		inline static _3DAssetLoaderThreadPkg s_3DAssetLoaderThread;
		inline static bool s_AssetLoaded = false;
		inline static ContentBrowserLayerNotifyCallback s_ContentBrowserLayerNotifyCallback;
		inline static ThreadInfoLayerNotifyCallback s_ThreadInfoLayerNotifyCallback;
	};
}


#endif // !OE1_EXECUTION_HANDLER_H_
