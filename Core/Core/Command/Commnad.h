#ifndef OE1_COMMAND_H_
#define OE1_COMMAND_H_

#include <string>
#include <queue>
#include "Util/LoadArgs.h"
#include "CommandDefinitions.h"
#include "Util/DataBlock.h"

namespace OE1Core
{
	/// <summary>
	///This command are invocked from the ui and need to queue them and execute them
	// after the UI call
	/// </summary>
	class Command
	{
		friend class ExecutionHandler;
	public:
		static void PushTextureLoadCommand(CommandDef::TextureLoadCommandDef _command);
		static void PushTextureLoadCommand(DataBlock::Image2D _data);
		static void PushAssetLoadCommand(Loader::LoadArgs _args);	
		static void PushEntitySelectionCommand(CommandDef::EntitySelectionCommandDef _command);
		static void PushMaterialTextureUpdateCommand(CommandDef::MaterialtextureUpdateCommandDef _command);
		static void PushMaterialTextureExtractionCommand(CommandDef::MaterialTextureExtractionDef _command);
	private:
		inline static std::queue<Loader::LoadArgs> s_Load3DAssetCommands;
		inline static std::queue<CommandDef::EntitySelectionCommandDef> s_EntitySelectionCommands;
		inline static std::queue<CommandDef::MaterialTextureExtractionDef> s_MaterialTextureExtractionCommands;
		inline static std::queue<CommandDef::TextureLoadCommandDef> s_TextureLoadCommands;
		inline static std::queue<DataBlock::Image2D> s_TextureLoadRawDataCommands;
		inline static std::queue<CommandDef::MaterialtextureUpdateCommandDef> s_MaterialTextureUpdateCommands;
		
	};
}


#endif // !OE1_COMMAND_H_
