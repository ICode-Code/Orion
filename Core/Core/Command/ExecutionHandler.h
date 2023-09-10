#ifndef OE1_EXECUTION_HANDLER_H_
#define OE1_EXECUTION_HANDLER_H_

#include "Util/LoadArgs.h"
#include "Geometry/GeometryLoader.h"
#include "../../AssetManager/AssetParser/AssetParser.h"
#include "Commnad.h"

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

	class ExecutionHandler
	{
	public:
		static void ProcessQueueCommands();

	protected:
		static void ProcessAssetLoadCommand();
		static void ProcessAsset();
		static void WriteBinary(std::ofstream& _file, std::string _data);
		


	private:
		inline static _3DAssetLoaderThreadPkg s_3DAssetLoaderThread;
		inline static bool s_AssetLoaded = false;
	};
}


#endif // !OE1_EXECUTION_HANDLER_H_
