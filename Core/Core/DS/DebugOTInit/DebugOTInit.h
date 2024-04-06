#ifndef OE1_DEBUG_OT_INIT_H_
#define OE1_DEBUG_OT_INIT_H_

#include <GL/glew.h>

namespace OE1Core
{
	namespace DS
	{
		class DebugOTInit
		{
		public:
			static void Init(class TurboOTNode& _node);
			static void Update(class TurboOTNode& _node);
		};
	}
}

#endif // !OE1_DEBUG_OT_INIT_H_
