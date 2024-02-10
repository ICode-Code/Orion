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

		s_MaterialIDTranslator.insert(std::make_pair((uint32_t)s_MaterialRegistry.size(), _name));
		s_MaterialRegistry.insert(std::make_pair(_name, new MasterMaterial(_shader, _name, (int)s_MaterialRegistry.size())));

		MasterMaterial* master_material = s_MaterialRegistry[_name];
		Memory::UniformBlockManager::LinkShader(_shader);
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

	void MaterialManager::RegisterMaterialView(MasterMaterial* _material)
	{
		// Make sure this material editor window isn't open already
		if (m_MaterialEditorWindow.find(_material->GetName()) != m_MaterialEditorWindow.end())
			return;

		m_MaterialEditorWindow.insert(std::make_pair(_material->GetName(), new MaterialViewWin(_material)));
		
		// Create Command
		CommandDef::MaterialTextureExtractionDef command;

		// Load Command
		command.Material = _material;
		command.MaterialView = m_MaterialEditorWindow[_material->GetName()];

		// Queue Command
		Command::PushMaterialTextureExtractionCommand(command);
	}
	void MaterialManager::RemoveMaterialView(MasterMaterial* _material)
	{
		if (m_MaterialEditorWindow.find(_material->GetName()) == m_MaterialEditorWindow.end())
			return;

		delete m_MaterialEditorWindow[_material->GetName()];
		m_MaterialEditorWindow.erase(_material->GetName());
	}
}