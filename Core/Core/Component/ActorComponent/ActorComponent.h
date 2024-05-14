#ifndef OE1_ACTOR_H_
#define OE1_ACTOR_H_


#include "../../Component/CameraComponent/CameraComponent.h"
#include "../../Component/CameraControllerComponent/BaseCameraControllerComponent.h"

namespace OE1Core
{
	class Entity;
	namespace Component
	{
		class ActorComponent
		{
		public:
			ActorComponent(Entity* _entity = nullptr, Component::CameraComponent* _camer = nullptr);
			~ActorComponent();

			Entity* GetActorEntity();
			void SetActorEntity(Entity* _entity);

			void SetCamera(Component::CameraComponent* _camer);
			Component::CameraComponent* GetCamera();


			void OnUpdate(float _dt);
			void OnEvent(OECore::IEvent& e);

		private:
			Component::CameraComponent* m_Camera = nullptr;
			Entity* m_ActorEntity = nullptr;
		};
	}
}

#endif // !OE1_ACTOR_H_
