#include "SceneManager.h"


namespace OE1Core
{

	SceneManager::~SceneManager()
	{
		for (auto scene : s_Scenes)
			delete scene.second;
		s_Scenes.clear();
	}
	Scene* SceneManager::GetActiveScene()
	{
		return s_ActiveScene;
	}

	void SceneManager::RegisterScene(std::string _name, Scene* _scene, bool _set_active)
	{
		if (s_Scenes.find(_name) == s_Scenes.end())
		{
			s_Scenes.insert(std::make_pair(_name, _scene));
			if (_set_active)
				s_ActiveScene = s_Scenes[_name];
		}
		else
		{
			LOG_ERROR("Failed to register scene: Scene name alreadu exist! {0}", _name);
		}
	}
	void SceneManager::ActivateScene(std::string _name)
	{
		if (s_Scenes.find(_name) == s_Scenes.end())
		{
			LOG_ERROR("Failed to activate the scene: scene not found! {0}", _name);
		}
		else
			s_ActiveScene = s_Scenes[_name];
	}
}