#ifndef OE1_SCENE_H_
#define OE1_SCENE_H_

#include <unordered_map>

#include <Entt/entt.hpp>
#include "../Mesh/StaticMesh/StaticMesh.h"

namespace OE1Core
{
	class Entity;
	class Scene
	{
	public:
		Scene();
		~Scene();

		Entity CreateEntity();
		Entity GetEntity(entt::entity _id);
		Entity GetEntity(uint32_t _id);

		void Update();
		void ResetPhysics();
		/// <summary>
		/// This include the physics
		/// </summary>
		void ResetScene();


	public:
		entt::registry m_EntityRegistry;
		std::unordered_map<uint32_t, StaticMesh> m_StaticMeshRegistry;
		
	};
}



#endif // !OE1_SCENE_H_
