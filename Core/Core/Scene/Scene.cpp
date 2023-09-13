#include "Scene.h"
#include "Entity.h"

namespace OE1Core
{
	Scene::Scene(SDL_Window* _window)
		: m_Window{_window}, m_CameraPkg{ _window }
	{
		m_Grid = new Grid();
	}
	Scene::~Scene()
	{
		delete m_Grid;
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
		m_CameraPkg.GetCamera()->SetResolution(glm::vec2((float)_width, (float)_height));
	}
	void Scene::Update(float dt)
	{
		m_CameraPkg.Update(dt);
	}
	void Scene::ResetPhysics()
	{

	}
	void Scene::OnEvent(OECore::IEvent& e)
	{
		m_CameraPkg.OnEvent(e);
	}
	void Scene::ResetScene()
	{
		ResetPhysics();
	}


}