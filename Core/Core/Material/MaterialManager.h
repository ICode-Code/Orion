#ifndef OE1_MATERIAL_MANAGER_H_
#define OE1_MATERIAL_MANAGER_H_

#include "MasterMaterial.h"
#include <unordered_map>

namespace OE1Core
{
	class MaterialManager
	{
		friend class CoreSystem;
	public:
		MaterialManager() = default;
		~MaterialManager();
		using MaterialRegistry = std::unordered_map<std::string, MasterMaterial*>;
		static MasterMaterial* RegisterMaterial(std::string _name, Shader* _shader);
		static MasterMaterial* GetMaterial(std::string _name);
		static MasterMaterial* GetMaterial(uint32_t _id);



	protected:
		inline static std::unordered_map<std::string, MasterMaterial*> s_MaterialRegistry;
		inline static std::unordered_map<uint32_t, std::string> s_MaterialIDTranslator;
		

	private:
		static std::string HandleNameDuplication(std::string _name);
	};
}

#endif // !OE1_MATERIAL_MANAGER_H_
