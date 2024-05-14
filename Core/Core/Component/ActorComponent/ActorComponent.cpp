#include "ActorComponent.h"
#include "../../Scene/Entity.h"

namespace OE1Core
{
	namespace Component
	{
		ActorComponent::ActorComponent(Entity* _entity, Component::CameraComponent* _camera)
		{
			if(_entity)
				m_ActorEntity = new Entity(_entity->GetHandle(), _entity->GetScene());
			m_Camera = _camera;
		}
		ActorComponent::~ActorComponent()
		{
			delete m_ActorEntity;
		}

		Entity* ActorComponent::GetActorEntity() { return m_ActorEntity; }
		void ActorComponent::SetActorEntity(Entity* _entity)
		{
			if (m_ActorEntity)
				delete m_ActorEntity;

			m_ActorEntity = new Entity(_entity->GetHandle(), _entity->GetScene());
		}

		void ActorComponent::SetCamera(Component::CameraComponent* _camera)
		{
			m_Camera = _camera;
		}
		Component::CameraComponent* ActorComponent::GetCamera() { return m_Camera; }

		void ActorComponent::OnUpdate(float _dt)
		{
			if (!m_ActorEntity)
				return;

			if (m_ActorEntity->HasComponent<Component::ThirdPersonCharacterControllerComponent>())
				m_ActorEntity->GetComponent<Component::ThirdPersonCharacterControllerComponent>().UpdateTargetTransform(_dt);

			if (m_Camera)
			{
				if (m_Camera->GetController())
					m_Camera->GetController()->UpdateInput(_dt);

				m_Camera->UpdateBuffer(_dt);
			}

		}
		void ActorComponent::OnEvent(OECore::IEvent& e)
		{
			if (!m_Camera || !m_Camera->GetController())
				return;

			m_Camera->GetController()->OnEvent(e);
		}
	}
}