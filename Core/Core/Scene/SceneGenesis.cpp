#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"

namespace OE1Core
{


	void Scene::UpdateFrameRes_Genesis(int _width, int _height)
	{
		m_GenesisController->UpdateFrameRes(_width, _height);
	}

	void Scene::InputUpdate_Genesis(float _dt)
	{
		m_GenesisController->InputUpdate(_dt);
	}
	void Scene::BufferUpdate_Genesis(float _dt)
	{
		m_GenesisController->UpdateBuffer(_dt);
	}
	void Scene::InitRender_Genesis()
	{
		m_GenesisController->InitRender();
	}
	void Scene::OnEvent_Genesis(OECore::IEvent& e)
	{
		m_GenesisController->OnEvent(e);
	}
}