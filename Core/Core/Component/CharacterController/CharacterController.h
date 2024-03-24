#ifndef OE1_CHARACTER_CONTROLLER_H_
#define OE1_CHARACTER_CONTROLLER_H_

#include "../CameraComponent/CameraComponent.h"
#include "../TransformComponent/TransformComponent.h"
#include "../AnimationComponent/AnimationComponent.h"
#include "IEvent/IEvent.h"

namespace OE1Core
{
	namespace Component
	{
		class CharacterController
		{
		public:
			CharacterController();
			~CharacterController();

			virtual void UpdateTargetTransform(float dt) = 0;
			virtual void OnEvent(OECore::IEvent& e)  = 0;
		};
	}
}


#endif // !OE1_CHARACTER_CONTROLLER_H_
