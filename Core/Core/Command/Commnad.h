#ifndef OE1_COMMAND_H_
#define OE1_COMMAND_H_

#include <string>
#include <queue>

namespace OE1Core
{

	enum class RT_COMMANDS
	{
		ASSET_LOAD		= 0,
		SELECT_ENTITY	= 1
	};

	/// <summary>
	///This command are invocked from the ui and need to queue them and execute them
	// after the UI call
	/// </summary>
	class Command
	{
		friend class ExecutionHandler;
	public:
		static void PushLoadCommand(std::string _path);	

	private:
		inline static std::queue<std::string> s_Load3DAssetCommands;
	};
}


#endif // !OE1_COMMAND_H_
