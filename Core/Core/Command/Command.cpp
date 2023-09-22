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
}