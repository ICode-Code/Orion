#ifndef OE1_COMMAND_DEFINATIONS_H_
#define OE1_COMMAND_DEFINATIONS_H_

#include <GL/glew.h>

namespace OE1Core
{
	namespace CommandDef 
	{
		struct EntitySelectionCommandDef
		{
			int posX;
			int posY;
			bool Batch = false;
			GLuint FrameID;
		};
	}
}

#endif // !OE1_COMMAND_DEFINATIONS_H_
