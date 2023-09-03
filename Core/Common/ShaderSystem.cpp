#include "ShaderSystem.h"


namespace OE1Core
{
	ShaderSystem::ShaderSystem()
	{

	}
	ShaderSystem::~ShaderSystem()
	{

	}
	ShaderManager::ShaderRegistry& ShaderSystem::GetShaderRegistry()
	{
		return ShaderManager::s_Shaders;
	}
	Shader* ShaderSystem::GetShader(ShaderID _id)
	{
		return ShaderManager::GetShader(_id);
	}
}