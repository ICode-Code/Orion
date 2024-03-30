#include "AnimationController.h"
#include "../../Core/CoreAnimation/AnimationManager/AnimationManager.h"

namespace OE1Core
{
	namespace Component
	{
		AnimationController::AnimationController(uint32_t _ent)
		{
			m_EntityID = _ent;
		}
		AnimationController::~AnimationController()
		{

		}

		void AnimationController::Update()
		{

		}
		bool AnimationController::ValidState(ANIMATION_STATE _state)
		{
			return m_BindedStateAnimations[_state] != nullptr;
		}
		void AnimationController::BindVoidState(ANIMATION_STATE _state, std::string _name)
		{
			m_BindedStateAnimations[_state] = nullptr;
			m_BindedStateAnimationName[_name] = _state;
		}
		void AnimationController::BindState(ANIMATION_STATE _state, Animation* _animation, std::string _name)
		{
			m_BindedStateAnimations[_state] = _animation;
			m_BindedStateAnimationName[_name] = _state;
		}
		ANIMATION_STATE AnimationController::GetActiveAnimationState()
		{
			return m_ActiveState;
		}
		void AnimationController::SetActiveState(ANIMATION_STATE _state)
		{
			if (m_ActiveState == _state)
				return;

			if (m_BindedStateAnimations.find(_state) == m_BindedStateAnimations.end())
				return;

			if (!m_BindedStateAnimations[_state])
				return;

			if (m_BindedStateAnimations[_state]->OnTransition())
				return;

			AnimationManager::UpdateAnimation(m_BindedStateAnimations[_state], m_EntityID);
			
			if(m_BindedStateAnimations[_state]->GetName() == SkeletonAnimator::s_AnimationSet[m_EntityID]->GetName()) // If the update is succesfful
				m_ActiveState = _state; // update state

		}
		void AnimationController::SetDefaultState(ANIMATION_STATE _state)
		{
			if (m_BindedStateAnimations.find(_state) == m_BindedStateAnimations.end())
				return;

			m_DefaultState = _state;
		}

		bool AnimationController::ApplyDefaultState()
		{
			if (m_BindedStateAnimations.find(m_DefaultState) == m_BindedStateAnimations.end())
				return false;

			m_ActiveState = m_DefaultState;
			AnimationManager::UpdateAnimation(m_BindedStateAnimations[m_ActiveState], m_EntityID);

			return true;
		}
		bool AnimationController::HasDefaultState()
		{
			return m_DefaultState != ANIMATION_STATE::T_POS;
		}
	}
}