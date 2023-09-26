#ifndef OE1_SCENE_MANAGER_H_
#define OE1_SCENE_MANAGER_H_

#include "Scene.h"
#include "UniformBuffer/UniformBlockManager.h"
#include "SceneEntityFactory.h"
#include "../ActiveEntity/ActiveEntity.h"
#include "EntityType.h"

#include <Log.h>
#include <memory>

namespace OE1Core
{
	class SceneManager
	{
	protected:
		~SceneManager();
	public:
		static void RegisterScene(std::string _name, Scene* _scene, bool _set_active = false);
		static void ActivateScene(std::string _name);
		static Scene* GetActiveScene();
		static void UpdateScene(float _dt);
		static void OnEvent(OECore::IEvent& e);
		static void RenderScenes();

	protected:
		inline static Scene* s_ActiveScene = nullptr;
		inline static SceneEntityFactory s_SceneEntityFactory;
		inline static std::unordered_map<std::string, Scene*> s_Scenes;
	};
}

#endif // !OE1_SCENE_MANAGER_H_
