#include "SourceEditorManager.h"


namespace OE1Core
{
	SourceEditorManager::SourceEditorManager()
	{ }
	SourceEditorManager::~SourceEditorManager()
	{
		for (auto iter : s_SourceEditors)
			delete iter.second;
	}

	void SourceEditorManager::Render()
	{
		for (auto iter : s_SourceEditors)
		{
			iter.second->Update();
			iter.second->Render();


		}
	}
	void SourceEditorManager::Update()
	{

	}

	void SourceEditorManager::Register(std::string _name, Component::ScriptComponent& _script)
	{
		if (s_SourceEditors.find(_name) != s_SourceEditors.end())
			return;

		s_SourceEditors.insert(std::make_pair(_name, new LuaSourceEditor(&_script)));
		s_SourceEditors[_name]->SetPurgCallback(std::bind(&SourceEditorManager::Purge, std::placeholders::_1));
	}
	void SourceEditorManager::Purge(std::string _name)
	{
		if (s_SourceEditors.find(_name) == s_SourceEditors.end())
			return;

		delete s_SourceEditors[_name];
		s_SourceEditors.erase(_name);
	}
}