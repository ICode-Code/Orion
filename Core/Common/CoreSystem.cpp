#include "CoreSystem.h"


namespace OE1Core
{
	CoreSystem::CoreSystem()
	{

	}
	CoreSystem::~CoreSystem()
	{

	}

	Shader* CoreSystem::GetShader(ShaderID _id)
	{
		return ShaderManager::GetShader(_id);
	}
}