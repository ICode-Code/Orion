#ifndef OE1_SCENE_INTERFACE_H_
#define OE1_SCENE_INTERFACE_H_

#include "../../Core/Scene/Entity.h"
#include "../../Core/Scene/SceneManager.h"


namespace OE1Core
{
	class SceneInterface
	{
	public:
		virtual ~SceneInterface() = default;
		virtual void UpdateScene() = 0;
		virtual Scene* GetScene() = 0;
		virtual Entity GetEntityByID(uint32_t _id) = 0;
		virtual entt::registry& GetSceneRegistry() = 0;
		virtual Grid* GetSceneGrid() = 0;
	};
}

#endif // !OE1_SCENE_INTERFACE_H_
