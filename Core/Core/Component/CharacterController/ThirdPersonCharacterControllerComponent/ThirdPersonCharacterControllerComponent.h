#ifndef OE1_THIRD_PERSON_CHARACTER_CONTROLLER_H_
#define OE1_THIRD_PERSON_CHARACTER_CONTROLLER_H_

#include <SDL.h>
#include "../CharacterController.h"

namespace OE1Core
{
	namespace Component
	{
		class ThirdPersonCharacterControllerComponent : public CharacterController
		{
			friend class InspectorComponent;
		public:
			ThirdPersonCharacterControllerComponent(
				Component::TransformComponent* _target,
				Component::CameraComponent* _camera,
				Component::AnimationController* _animation = nullptr);
			~ThirdPersonCharacterControllerComponent();

			virtual void UpdateTargetTransform(float dt);
			virtual void OnEvent(OECore::IEvent& e);

			void SetCameraComponent(Component::CameraComponent* _camera);
			Component::CameraComponent* GetCameraComponent();

			void SetTargetAnimationController(Component::AnimationController* _controller);
			Component::AnimationController* GetAnimationController();

			void SetTargetTransform(TransformComponent* _target, Entity* _host_entity = nullptr);
			TransformComponent* GetTargetTransform();
			

		private:
			Component::CameraComponent* m_TargetCamera = nullptr;
			Component::AnimationController* m_TargetAnimationController = nullptr;
			Component::TransformComponent* m_TargetTransform = nullptr;
			const Uint8* m_TPCCFreeKeyInputState = SDL_GetKeyboardState(NULL);

		private:
			void TPCC_ProcessRapidKeyInput(float dt);
			bool TPCC_KeyPressEvent(OECore::KeyPressedEvent& _event);
			bool TPCC_KeyReleaseEvent(OECore::KeyReleaseEvent& _event);

		private: // key State
			bool m_SprintKeyPressed = false;

		private: // param
			float m_WalkSpeed = 2.5f;
			float m_TurnSpeed = 180.0f; // in deg
			float m_SprintSpeed = 10.0f;
			float m_AlignmentThreshold = 0.98f;

			float m_CurrentMoveSpeed = 0.0f;
			float m_CurrentTurnSpeed = 0.0f;


		};
	}
}
#endif // !OE1_THIRD_PERSON_CHARACTER_CONTROLLER_H_
