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

		Memory::UniformBlockManager::LinkShader(_shader);
		s_MaterialIDTranslator.insert(std::make_pair((uint32_t)s_MaterialRegistry.size(), _name));
		s_MaterialRegistry.insert(std::make_pair(_name, new MasterMaterial(_shader, _name, (int)s_MaterialRegistry.size())));

		MasterMaterial* master_material = s_MaterialRegistry[_name];
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::MATERIAL_REGISTRY)->Update(Memory::s_MaterialPropertiesBufferSize, master_material->GetOffset(), &master_material->m_Parameter);
		Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::TAI_REGISTRY)->Update(Memory::s_TextureAccessIndexBufferSize, master_material->GetOffset(), &master_material->m_TAI);
		return s_MaterialRegistry[_name];
	}
	MasterMaterial* MaterialManager::GetMaterial(std::string _name)
	{
		if (s_MaterialRegistry.find(_name) != s_MaterialRegistry.end())
			return s_MaterialRegistry[_name];

		return nullptr;
	}
	MasterMaterial* MaterialManager::GetMaterial(uint32_t _id)
	{
		if(s_MaterialIDTranslator.find(_id) != s_MaterialIDTranslator.end())
			return s_MaterialRegistry[s_MaterialIDTranslator[_id]];

		return nullptr;
	}
}