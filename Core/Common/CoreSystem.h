#ifndef OE1_CORE_SYSTEM_H_
#define OE1_CORE_SYSTEM_H_

#include "Interface/CoreSystemInterface.h"

namespace OE1Core
{


	/// <summary>
	/// This clas help as interface for accessing the core engine element to renderer
	/// or any other lib who wan to access the core element
	/// </summary>
	class CoreSystem : public CoreSystemInterface
	{
	public:
		CoreSystem();
		~CoreSystem();

		Shader* GetShader(ShaderID _id) override;
		spdlog::logger* GetLog() override;
		void SetRenderedFrame(unsigned int _id) override;
		ShaderManager::ShaderRegistry* GetShaderRegistry() override;
		MaterialManager::MaterialRegistry* GetMaterialRegistry() override;
		MasterMaterial* GetMaterial(std::string _id) override;
		MasterMaterial* GetMaterial(uint32_t _id) override;
	};
}

#endif // !OE1_CORE_SYSTEM_H_
