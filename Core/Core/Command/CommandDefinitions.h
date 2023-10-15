#ifndef OE1_COMMAND_DEFINATIONS_H_
#define OE1_COMMAND_DEFINATIONS_H_

#include <GL/glew.h>

namespace OE1Core
{
	class MaterialViewWin;
	class MasterMaterial;

	namespace CommandDef 
	{
		struct EntitySelectionCommandDef
		{
			int posX;
			int posY;
			bool Batch = false;
			GLuint FrameID;
		};
		struct TextureLoadCommandDef
		{
			std::string Name;
			std::string Path;
		};

		struct MaterialTextureExtractionDef
		{
			MaterialViewWin*	MaterialView = nullptr;
			MasterMaterial*	Material = nullptr;
		};
	}
}

#endif // !OE1_COMMAND_DEFINATIONS_H_
