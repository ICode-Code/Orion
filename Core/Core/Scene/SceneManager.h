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
	struct RenderThreadArgs
	{
		SDL_Window* Window;
		SDL_GLContext Context;
	};
	class SceneManager
	{
	protected:
		~SceneManager();
	public:
		// This will remove the active entity from the active scene
		static ActiveEntity* QueryActiveEntity();
		static void PurgActiveEntity();
		static void RegisterScene(std::string _name, Scene* _scene, bool _set_active = false);
		static void ActivateScene(std::string _name);
		static Scene* GetActiveScene();
		static void OnEvent(OECore::IEvent& e);
		static void OnEventGenesis(OECore::IEvent& e);

		static void UpdateSceneInEngine(float _dt);
		static void RenderScenesInEngine();

		static void UpdateSceneInGame(float _dt);
		static void RenderScenesInGame();

		/// <summary>
		/// Nothing
		/// </summary>
		/// <param name="_window"></param>
		/// <param name="_context"></param>
		/// <returns></returns>
		static int RenderThreadCall(SDL_Window* _window, SDL_GLContext _context);

	protected:
		inline static Scene* s_ActiveScene = nullptr;
		inline static SceneEntityFactory s_SceneEntityFactory;
		inline static std::unordered_map<std::string, Scene*> s_Scenes;
	};
}

#endif // !OE1_SCENE_MANAGER_H_
