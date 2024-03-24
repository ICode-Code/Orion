#include "AnimationController.h"


namespace OE1Core
{
	namespace Component
	{
		AnimationController::AnimationController()
		{

		}
		AnimationController::~AnimationController()
		{

		}

		void AnimationController::Update()
		{

		}
		void AnimationController::BindState(ANIMATION_STATE _state, Animation* _animation)
		{
			m_BindedStateAnimations[_state] = _animation;
		}
		ANIMATION_STATE AnimationController::GetActiveAnimationState()
		{
			return m_ActiveState;
		}
		void AnimationController::SetActiveState(ANIMATION_STATE _state)
		{
			if (m_BindedStateAnimations.find(_state) == m_BindedStateAnimations.end())
				return;

			m_ActiveState = _state;
		}
	}
}