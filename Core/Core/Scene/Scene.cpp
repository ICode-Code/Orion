#include "Scene.h"
#include "Entity.h"

namespace OE1Core
{
	Scene::Scene(GLFWwindow* _window)
		: m_Window{_window}, m_CameraPkg{ m_Window }
	{

	}
	Scene::~Scene()
	{

	}


	Entity Scene::CreateEntity()
	{
		return Entity(m_EntityRegistry.create(), this);
	}
	Entity Scene::GetEntity(entt::entity _id)
	{
		if (!m_EntityRegistry.valid(_id))
		{
			LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity(_id, this);
	}
	Entity Scene::GetEntity(uint32_t _id)
	{
		if (!m_EntityRegistry.valid((entt::entity)_id))
		{
			LOG_ERROR("Unable to retrive entity: Invalid ID");
			return Entity();
		}
		return Entity((entt::entity)_id, this);
	}
	void Scene::Update(int _width, int _height)
	{
		m_RendererUpdateCallback(_width, _height);
	}
	void Scene::Update(float dt)
	{
		m_CameraPkg.Update(dt);
	}
	void Scene::ResetPhysics()
	{

	}
	void Scene::OnEvent(Event& e)
	{
		m_CameraPkg.OnEvent(e);
	}
	void Scene::ResetScene()
	{
		ResetPhysics();
	}


}