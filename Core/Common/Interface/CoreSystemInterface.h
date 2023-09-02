#ifndef OE1_CORE_SYSTEM_INTERFACE_H_
#define OE1_CORE_SYSTEM_INTERFACE_H_

#include "../../Core/Scene/SceneManager.h"
#include "ShaderManager/ShaderManager.h"

namespace OE1Core
{
	class CoreSystemInterface
	{
	public:
		virtual ~CoreSystemInterface() = default;

		virtual Shader* GetShader(ShaderID _id) = 0;
	};
}

#endif // !OE1_CORE_SYSTEM_INTERFACE_H_
