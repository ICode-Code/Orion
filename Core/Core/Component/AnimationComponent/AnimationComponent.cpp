#include "AnimationComponent.h"


namespace OE1Core
{
	namespace Component
	{
		AnimationComponent::AnimationComponent(Animation* _animation, uint32_t _entity, MemoryBufferLocator _buffer_locator)
			: m_BufferLocator(_buffer_locator), m_EntityID(_entity)
		{
			m_AnimationController = new AnimationController(m_EntityID);
			if (_animation)
			{
				m_Animation = new Animation(_animation->GetBoneCount());
				*m_Animation = *_animation;
			}
			else
				m_Animation = nullptr;
		}
		AnimationComponent::~AnimationComponent()
		{
			delete m_AnimationController;
			delete m_Animation;
		}
		void AnimationComponent::SwitchAnimation(Animation* _animation)
		{
			if (!m_Animation)
				SetAnimation(_animation);

			// If the animation manager knows animation with this
			// EntityID it means this animation pointer is already registered
			// so we just need to interpolate b/n the new one and the old one
			if (AnimationManager::HasAnimation(m_EntityID))
				AnimationManager::UpdateAnimation(_animation, m_EntityID);

			m_LinkWithStateMachine = false;
		}
		void AnimationComponent::LinkStateMachine()
		{
			if (m_AnimationController->m_BindedStateAnimations.size() <= 0)
			{

				return;
			}

			if (!m_AnimationController->HasDefaultState())
			{

				return;
			}

			m_AnimationController->ApplyDefaultState();

		}
		void AnimationComponent::SetAnimation(Animation* _animation)
		{ 
			if (!m_Animation)
				m_Animation = new Animation(_animation->GetBoneCount());
			// Copy the value
			*m_Animation = *_animation;

			if (!AnimationManager::HasAnimation(m_EntityID))
			{
				m_BufferLocator = AnimationManager::RegisterAnimationInstance(m_Animation, m_EntityID);
				m_SkinnedMeshComponentUpdateCallback(m_BufferLocator.BufferIndex);
			} else 
				AnimationManager::HardSwitch(m_Animation, m_EntityID);

			
		}
		void AnimationComponent::SetSkinnedMeshComponentCallback(const std::function<void(int)>& _callback)
		{
			m_SkinnedMeshComponentUpdateCallback = _callback;
		}
		GLintptr AnimationComponent::GetOffset() { return m_BufferLocator.Offset; }

		void AnimationComponent::SetOffset(GLintptr _offset) { m_BufferLocator.Offset = _offset; }

		void AnimationComponent::SetAnimationBufferID(GLuint _id) { m_BufferLocator.BufferID = _id; }

		GLuint AnimationComponent::GetAnimationBufferID() { return m_BufferLocator.BufferID; }

		void AnimationComponent::UpdateBuffer()
		{

			m_AnimationController->Update();

			if (!m_Animation) return;

			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferLocator.BufferID);
			glBufferSubData(GL_UNIFORM_BUFFER, m_BufferLocator.BaseOffset, m_BufferLocator.Offset, m_Animation->m_BoneTransform.data());
			
			m_Animation->m_Updated = false;
		}

		void AnimationComponent::Update(float _dt)
		{

		}
		Animation* AnimationComponent::GetAnimation() { return m_Animation; }

		void AnimationComponent::SetUpdateBufferLocator(MemoryBufferLocator _new) 
		{ 
			m_BufferLocator = _new; 
		}
		AnimationController* AnimationComponent::GetAnimationController() { return m_AnimationController; }
		MemoryBufferLocator AnimationComponent::GetBufferLocator() { return m_BufferLocator; }

	}
}