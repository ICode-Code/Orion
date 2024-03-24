#ifndef OE1_ANIMATION_CONTROLLER_H_
#define OE1_ANIMATION_CONTROLLER_H_


#include "Animation/Animation.h"
#include "AnimationState.h"


#include <unordered_map>

namespace OE1Core
{
	namespace Component
	{
		class AnimationController
		{
		public:
			AnimationController();
			~AnimationController();

			void Update();
			void BindState(ANIMATION_STATE _state, Animation* _animation);
			void SetActiveState(ANIMATION_STATE _state);
			ANIMATION_STATE GetActiveAnimationState();

		private:
			std::unordered_map<ANIMATION_STATE, Animation*> m_BindedStateAnimations;
			ANIMATION_STATE m_ActiveState = ANIMATION_STATE::T_POS;
		};
	}
}

#endif // !OE1_ANIMATION_CONTROLLER_H_
