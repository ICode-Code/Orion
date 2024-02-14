#ifndef OE1_EXECUTION_HANDLE_BASE_H_
#define OE1_EXECUTION_HANDLE_BASE_H_

#include "Util/LoadArgs.h"
#include "Util/DataBlock.h"
#include "Util/LoaderUtil.h"
#include "Util/NameHandle.h"
#include "../../../InfiniteVision/IVMasterRenderer.h"
#include "../../../Scene/SceneManager.h"
#include "../../CoreCommand/Commnad.h"
#include <Log.h>

#include <functional>
#include <fstream>


using namespace std::chrono_literals;

namespace OE1Core
{
	namespace CommandHnd
	{
		class ExecutionHandleBase
		{
		public:
			ExecutionHandleBase(Scene* _scene);
			~ExecutionHandleBase();

			static Scene* GetScene();
			static void SetScene(Scene* _scene);
			static void WriteBinary(std::ofstream& _file, std::string _data);

		protected:
			inline static Scene* m_Scene = nullptr;
		};
	}
}

#endif // !OE1_EXECUTION_HANDLE_BASE_H_
