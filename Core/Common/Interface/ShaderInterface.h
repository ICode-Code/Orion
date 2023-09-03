#ifndef OE1_SHADER_INTERFACE_H_
#define OE1_SHADER_INTERFACE_H_


#include "ShaderManager/ShaderManager.h"


namespace OE1Core
{
	class ShaderInterface
	{
	public:
		virtual ~ShaderInterface() = default;
		virtual ShaderManager::ShaderRegistry& GetShaderRegistry() = 0;
		virtual Shader* GetShader(ShaderID _id) = 0;
	};
}

#endif // !OE1_SHADER_INTERFACE_H_
