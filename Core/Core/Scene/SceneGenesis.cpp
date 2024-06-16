#include "Scene.h"
#include "Entity.h"
#include "../ActiveEntity/ActiveEntity.h"

namespace OE1Core
{


	void Scene::UpdateFrameRes_Genesis(int _width, int _height)
	{
		m_GenesisController->UpdateFrameRes(_width, _height);
	}
	void Scene::UpdateAudioComponents_Genesis()
	{
		auto audio_source_view = m_EntityRegistry.view<Component::AudioSourceComponent>();

		for (auto ent : audio_source_view)
		{
			Component::AudioSourceComponent& _audio_source = audio_source_view.get<Component::AudioSourceComponent>(ent);

			_audio_source.Play();
		}
	}
	void Scene::InitOnce_Genesis()
	{
		UpdateAudioComponents_Genesis();
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