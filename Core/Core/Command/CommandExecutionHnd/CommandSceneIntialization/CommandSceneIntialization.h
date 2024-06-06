#ifndef OE1_COMMAND_SCENE_INITIALIZATION_H_
#define OE1_COMMAND_SCENE_INITIALIZATION_H_


#include "../ExeHandleBase/ExeHandleBase.h"


namespace OE1Core
{
	namespace CommandHnd
	{
		class CommandSceneInitalization : public ExecutionHandleBase
		{
		public:
			CommandSceneInitalization(Scene* _scene);
			~CommandSceneInitalization();

			static void ProcessQueue();

		private:
			static void ProcessIBLLoad();
			static void ProcessSkyBoxInitCommand();
		};
	}
}



#endif // !OE1_COMMAND_SCENE_INITIALIZATION_H_
