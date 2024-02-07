#include "Commnad.h"



namespace OE1Core
{
	void Command::PushAssetLoadCommand(Loader::LoadArgs _args)
	{
		s_Load3DAssetCommands.push(_args);
	}

	void Command::PushEntitySelectionCommand(CommandDef::EntitySelectionCommandDef _command) 
	{
		s_EntitySelectionCommands.push(_command);
	}
	void Command::PushMaterialTextureUpdateCommand(CommandDef::MaterialtextureUpdateCommandDef _command) 
	{
		s_MaterialTextureUpdateCommands.push(_command);
	}
	void Command::PushMasterRendererMaterialRefresh(CommandDef::MasterRendererMaterialRefreshCommandDef _command)
	{
		s_MasterRendererMaterialRefreshCommands.push(_command);
	}
	void Command::PushMaterialTextureExtractionCommand(CommandDef::MaterialTextureExtractionDef _command)
	{
		s_MaterialTextureExtractionCommands.push(_command);
	}
	void Command::PushTextureLoadCommand(CommandDef::TextureLoadCommandDef _command)
	{
		s_TextureLoadCommands.push(_command);
	}
	void Command::PushTextureLoadCommand(DataBlock::Image2D _data)
	{
		s_TextureLoadRawDataCommands.push(_data);
	}
	void Command::PushDynamicViewportPurgeCommand(CommandDef::PurgeDynamicViewportCommandDef _command)
	{
		s_DyanmicViewportPurgeCommands.push(_command);
	}
}