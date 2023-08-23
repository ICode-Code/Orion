#include "Commnad.h"



namespace OE1Core
{
	void Command::PushLoadCommand(std::string _path)
	{
		s_Load3DAssetCommands.push(_path);
	}
}