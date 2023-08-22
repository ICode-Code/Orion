#include "Scene.h"
#include "Entity.h"

namespace OE1Core
{
	Scene::Scene()
	{

	}
	Scene::~Scene()
	{

	}


	Entity Scene::CreateEntity()
	{
		return Entity(m_EntityRegistry.create(), this);
	}


}