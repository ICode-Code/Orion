#include "CoreSystem.h"
#include "Shared/ViewportArgs.h"


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
	spdlog::logger* CoreSystem::GetLog()
	{
		return &*Log::GetCoreLogger();
	}
	void CoreSystem::SetRenderedFrame(unsigned int _id)
	{
		ViewportArgs::FINAL_FRAME = _id;
	}
}