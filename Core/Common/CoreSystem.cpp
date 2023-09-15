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
	ShaderManager::ShaderRegistry* CoreSystem::GetShaderRegistry()
	{
		return &ShaderManager::s_Shaders;
	}
	MaterialManager::MaterialRegistry* CoreSystem::GetMaterialRegistry()
	{
		return &MaterialManager::s_MaterialRegistry;
	}
	MasterMaterial* CoreSystem::GetMaterial(std::string _id)
	{
		return MaterialManager::GetMaterial(_id);
	}
	MasterMaterial* CoreSystem::GetMaterial(uint32_t _id)
	{
		return MaterialManager::GetMaterial(_id);
	}
	void CoreSystem::SetRenderedFrame(unsigned int _id)
	{
		ViewportArgs::FINAL_FRAME = _id;
	}
}