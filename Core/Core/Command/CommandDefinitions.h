#ifndef OE1_COMMAND_DEFINATIONS_H_
#define OE1_COMMAND_DEFINATIONS_H_

#include <GL/glew.h>
#include "MaterialType.h"

namespace OE1Core
{
	class MaterialViewWin;
	class MasterMaterial;
	class Texture;

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
			std::string Destination;
		};

		struct MaterialTextureExtractionDef
		{
			MaterialViewWin*	MaterialView = nullptr;
			MasterMaterial*	Material = nullptr;
		};


		struct MaterialtextureUpdateCommandDef
		{
			// Which Texture
			MaterialType TextureType;
			// To which material
			MasterMaterial* Material = nullptr;

			Texture* NewTexture = nullptr;

			bool IsColor = false;

			int Layer = -1;
		};
	}
}

#endif // !OE1_COMMAND_DEFINATIONS_H_
