#ifndef OE1_CORE_SYSTEM_INTERFACE_H_
#define OE1_CORE_SYSTEM_INTERFACE_H_

#include "../../Core/Scene/SceneManager.h"
#include "ShaderManager/ShaderManager.h"
#include "../Core/Material/MaterialManager.h"

namespace OE1Core
{
	class CoreSystemInterface
	{
	public:
		virtual ~CoreSystemInterface() = default;

		virtual Shader* GetShader(ShaderID _id) = 0;
		virtual spdlog::logger* GetLog() = 0;
		virtual void SetRenderedFrame(unsigned int _id) = 0;
		virtual ShaderManager::ShaderRegistry* GetShaderRegistry() = 0;
		virtual MaterialManager::MaterialRegistry* GetMaterialRegistry() = 0;
		virtual MasterMaterial* GetMaterial(std::string _id) = 0;
		virtual MasterMaterial* GetMaterial(uint32_t _id) = 0;
	};
}

#endif // !OE1_CORE_SYSTEM_INTERFACE_H_
