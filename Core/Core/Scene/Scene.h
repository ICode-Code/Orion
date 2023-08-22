#ifndef OE1_SCENE_H_
#define OE1_SCENE_H_

#include <Entt/entt.hpp>


namespace OE1Core
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity();


	public:
		entt::registry m_EntityRegistry;
	};
}



#endif // !OE1_SCENE_H_
