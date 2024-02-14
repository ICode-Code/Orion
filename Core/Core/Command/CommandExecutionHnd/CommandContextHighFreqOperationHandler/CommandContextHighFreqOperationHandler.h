#ifndef OE1_COMMAND_CONTEXT_HIGH_FREQUENCY_OPERATION_HANDLER_H_
#define OE1_COMMAND_CONTEXT_HIGH_FREQUENCY_OPERATION_HANDLER_H_

#include "../ExeHandleBase/ExeHandleBase.h"

namespace OE1Core
{
	namespace CommandHnd
	{
		class CommandContextHighFreqOperationHandle : public ExecutionHandleBase
		{
		public:
			CommandContextHighFreqOperationHandle(Scene* _scene);
			~CommandContextHighFreqOperationHandle();

			static void ProcessQueue();


		private:
			static void ProcessClickReadbackCommand();

		};
	}
}

#endif // !OE1_COMMAND_CONTEXT_HIGH_FREQUENCY_OPERATION_HANDLER_H_
