#ifndef OE1_COMMAND_DEFINATIONS_H_
#define OE1_COMMAND_DEFINATIONS_H_

#include <GL/glew.h>
#include "MaterialType.h"
#include "AvailTexture.h"
#include "../../AssetLoader/src/Util/DataBlock.h"


#define ORI_COMMAND_DEF_ARGS(_func) __FILE__, __LINE__, _func

namespace OE1Core
{
	class MaterialViewWin;
	class MasterMaterial;
	class Texture;
	struct IVModel;

	namespace CommandDef 
	{
		struct CommandBase
		{
		public:
			CommandBase(std::string _file, int _line , std::string _func)
			{
				__CM_FILE = _file;
				__CM_LINE = _line;
				__CM_CALLER = _func;
			}
		public:
			std::string __CM_FILE;
			int __CM_LINE;
			std::string __CM_CALLER;
			bool Lock = false;
		};

		/// <summary>
		/// This command is intitated and queued when ever we select an entity
		/// </summary>
		struct EntitySelectionCommandDef : public CommandBase
		{
			EntitySelectionCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			int posX;
			int posY;
			bool Batch = false;
			GLuint FrameID;
		};

		/// <summary>
		/// This command is queued when we import texture from drive
		/// </summary>
		struct TextureLoadCommandDef : public CommandBase
		{
			TextureLoadCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			std::string Name;
			std::string Path;
			std::string Destination;
		};

		/// <summary>
		/// This command is queued when we click on material detail it prepare the texture 
		/// for preview purpose
		/// </summary>
		struct MaterialTextureExtractionDef : public CommandBase
		{
			MaterialTextureExtractionDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			MaterialViewWin*	MaterialView = nullptr;
			MasterMaterial*	Material = nullptr;
		};


		/// <summary>
		/// This command is queued when a material get updated
		/// and the master renderer needs to know so it can update the buffer
		/// and perform render with proper material
		/// </summary>
		struct MasterRendererMaterialRefreshCommandDef : public CommandBase
		{
			MasterRendererMaterialRefreshCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			MasterMaterial* Material;
			std::string Name;
			int Offset;
		};

		/// <summary>
		/// This command is queued or used when we register new material or create one
		/// this command will be queued inorder to take material snapshot/privew
		/// </summary>
		struct MaterialSnapShotCommandDefs : public CommandBase
		{
			MaterialSnapShotCommandDefs(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			MasterMaterial* Material;
			std::string Name;
			int Offset;
		};


		/// <summary>
		/// This command is queued when we add or update texture of a material
		/// when we drag and drop into the material view or add new
		/// </summary>
		struct MaterialtextureUpdateCommandDef : public CommandBase
		{
			MaterialtextureUpdateCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

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
		struct PurgeDynamicViewportCommandDef : public CommandBase
		{
			PurgeDynamicViewportCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			std::string Name;
		};


		struct MaterialCreationCommandDef : public CommandBase
		{
			MaterialCreationCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			MaterialTextureCount TextureCount;
			MaterialTextureAvailFlags TextureFlag;
			AvailTexture AvialTextures;
			std::unordered_map<DataBlock::TextureType, std::string> Textuers;
			std::string MaterialName;
			uint32_t TargetMeshID;
			uint32_t LocalSubMeshID;
		};

		struct ModelPreviewRenderCommandDef : public CommandBase
		{
			ModelPreviewRenderCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			IVModel* Model = nullptr;
		};

		struct DynamicMeshModelPreviewRenderCommandDef : public CommandBase
		{
			DynamicMeshModelPreviewRenderCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}

			IVModel* Model = nullptr;
		};

		struct AnimationLoadCommandDef : public CommandBase
		{
			AnimationLoadCommandDef(std::string _file, int _line, std::string _func)
				: CommandBase(_file, _line, _func)
			{}
			
			std::string Path;
			DataBlock::BoneMap bone_map;
			uint32_t PackageID;
		};
	}
}

#endif // !OE1_COMMAND_DEFINATIONS_H_
