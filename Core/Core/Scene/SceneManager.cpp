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
	void SceneManager::UpdateScene(float _dt)
	{
		 s_ActiveScene->Update(_dt);

		 Memory::UniformBlockManager::UseBuffer(Memory::UniformBufferID::SCENE_TRANSFORM)->Update(Memory::s_SceneTransformBufferSize, 0, &s_ActiveScene->m_CameraPkg.GetSceneTransform());
	
	}
	void SceneManager::OnEvent(OECore::IEvent& e)
	{
		s_ActiveScene->OnEvent(e);
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