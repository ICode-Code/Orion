#ifndef OE1_SHADER_SYSTEM_H_
#define OE1_SHADER_SYSTEM_H_

#include "Interface/ShaderInterface.h"

namespace OE1Core
{
	class ShaderSystem : public ShaderInterface
	{
	public:
		ShaderSystem();
		~ShaderSystem();

		ShaderManager::ShaderRegistry& GetShaderRegistry() override;
		Shader* GetShader(ShaderID _id) override;
	};
}

#endif // !OE1_SHADER_SYSTEM_H_
