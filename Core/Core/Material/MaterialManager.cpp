#include "MaterialManager.h"


namespace OE1Core
{
	MaterialManager::~MaterialManager()
	{
		for (auto iter : s_MaterialRegistry)
			delete iter.second;
		s_MaterialRegistry.clear();
	}

	std::string MaterialManager::HandleNameDuplication(std::string _name)
	{


		return _name;
	}

	MasterMaterial* MaterialManager::RegisterMaterial(std::string _name, Shader* _shader)
	{
		if (s_MaterialRegistry.find(_name) != s_MaterialRegistry.end())
			_name = HandleNameDuplication(_name);

		s_MaterialRegistry.insert(std::make_pair(_name, new MasterMaterial(_shader, _name, (int)s_MaterialRegistry.size())));

		return s_MaterialRegistry[_name];
	}
	MasterMaterial* MaterialManager::GetMaterial(std::string _name)
	{
		if (s_MaterialRegistry.find(_name) != s_MaterialRegistry.end())
			return s_MaterialRegistry[_name];

		return nullptr;
	}
}