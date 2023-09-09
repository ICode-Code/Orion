#ifndef OE1_MATERIAL_MANAGER_H_
#define OE1_MATERIAL_MANAGER_H_

#include "MasterMaterial.h"
#include "PreDef.h"
#include <unordered_map>

namespace OE1Core
{
	class MaterialManager
	{
	public:
		MaterialManager() = default;
		~MaterialManager();

		static MasterMaterial* RegisterMaterial(std::string _name, Shader* _shader);
		static MasterMaterial* GetMaterial(std::string _name);


	protected:
		inline static std::unordered_map<std::string, MasterMaterial*> s_MaterialRegistry;
		

	private:
		static std::string HandleNameDuplication(std::string _name);
	};
}

#endif // !OE1_MATERIAL_MANAGER_H_
