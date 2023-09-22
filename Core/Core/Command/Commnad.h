#ifndef OE1_COMMAND_H_
#define OE1_COMMAND_H_

#include <string>
#include <queue>
#include "Util/LoadArgs.h"
#include "CommandDefinitions.h"

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
		static void PushAssetLoadCommand(Loader::LoadArgs _args);	
		static void PushEntitySelectionCommand(CommandDef::EntitySelectionCommandDef _command);

	private:
		inline static std::queue<Loader::LoadArgs> s_Load3DAssetCommands;
		inline static std::queue<CommandDef::EntitySelectionCommandDef> s_EntitySelectionCommands;
	};
}


#endif // !OE1_COMMAND_H_
