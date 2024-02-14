#ifndef OE1_COMMAND_IGNITION_EXECUTION_HANDLER_H_
#define OE1_COMMAND_IGNITION_EXECUTION_HANDLER_H_

#include "../ExeHandleBase/ExeHandleBase.h"


namespace OE1Core
{
	namespace CommandHnd
	{
		class CommandIgnitionExecutionHandle : public ExecutionHandleBase
		{
		public:
			CommandIgnitionExecutionHandle(Scene* _scene);
			~CommandIgnitionExecutionHandle();

			static void ProcessQueue();

		};
	}
}

#endif // !OE1_COMMAND_IGNITION_EXECUTION_HANDLER_H_
