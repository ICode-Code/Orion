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
		/// <summary>
		/// This command is intitated and queued when ever we select an entity
		/// </summary>
		struct EntitySelectionCommandDef
		{
			int posX;
			int posY;
			bool Batch = false;
			GLuint FrameID;
		};

		/// <summary>
		/// This command is queued when we import texture from drive
		/// </summary>
		struct TextureLoadCommandDef
		{
			std::string Name;
			std::string Path;
			std::string Destination;
		};

		/// <summary>
		/// This command is queued when we click on material detail it prepare the texture 
		/// for preview purpose
		/// </summary>
		struct MaterialTextureExtractionDef
		{
			MaterialViewWin*	MaterialView = nullptr;
			MasterMaterial*	Material = nullptr;
		};


		/// <summary>
		/// This command is queued when a material get updated
		/// and the master renderer needs to know so it can update the buffer
		/// and perform render with proper material
		/// </summary>
		struct MasterRendererMaterialRefreshCommandDef 
		{
			MasterMaterial* Material;
			std::string Name;
			int Offset;
		};

		/// <summary>
		/// This command is queued or used when we register new material or create one
		/// this command will be queued inorder to take material snapshot/privew
		/// </summary>
		struct MaterialSnapShotCommandDefs
		{
			MasterMaterial* Material;
			std::string Name;
			int Offset;
		};


		/// <summary>
		/// This command is queued when we add or update texture of a material
		/// when we drag and drop into the material view or add new
		/// </summary>
		struct MaterialtextureUpdateCommandDef
		{
			// Which Texture
			MaterialType TextureType;

			// To which material
			MasterMaterial* Material = nullptr;

			Texture* NewTexture = nullptr;
		};

		/// <summary>
		/// This commnad is queued when the user click 
		/// the close button in a dynamic viewport
		/// </summary>
		struct PurgeDynamicViewportCommandDef
		{
			std::string Name;
		};
	}
}

#endif // !OE1_COMMAND_DEFINATIONS_H_
