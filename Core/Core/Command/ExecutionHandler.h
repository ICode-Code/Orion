#ifndef OE1_EXECUTION_HANDLER_H_
#define OE1_EXECUTION_HANDLER_H_

#include "Commnad.h"
#include <thread>
#include <mutex>
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
		static void __exe();
		


	private:
		inline static _3DAssetLoaderThreadPkg s_3DAssetLoaderThread;
		inline static std::mutex s_3DAssetLoaderMutex;

	private: // just for now
		static void junk_run(std::string _run_info, bool& _is_running)
		{
			_is_running = true;
			std::this_thread::sleep_for(10s);
			LOG_WARRNING("Running... {0}", _run_info);
			_is_running = false;
		}
	};
}


#endif // !OE1_EXECUTION_HANDLER_H_
