#include "AnimationComponent.h"


namespace OE1Core
{
	namespace Component
	{
		AnimationComponent::AnimationComponent(Animation* _animation, GLintptr _offset, GLuint _animation_buffer)
		{
			m_Animation = _animation;
			m_Offset = _offset;
			m_AnimationBuffer = _animation_buffer;

			size_t _bone_count = (size_t)_animation->GetBoneCount();
			m_BoneTransform.reserve(_bone_count);
			for (int i = 0; i < _bone_count; i++)
				m_BoneTransform.push_back(glm::mat4(1.0f));
		}
		AnimationComponent::~AnimationComponent()
		{

		}

		GLintptr AnimationComponent::GetOffset()
		{
			return m_Offset;
		}
		void AnimationComponent::SetOffset(GLintptr _offset)
		{
			m_Offset = _offset;
		}

		void AnimationComponent::SetAnimationBufferID(GLuint _id)
		{
			m_AnimationBuffer = _id;
		}
		GLuint AnimationComponent::GetAnimationBufferID()
		{
			return m_AnimationBuffer;
		}
		void AnimationComponent::UpdateBuffer()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_AnimationBuffer);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, m_Animation->GetBoneCount() * sizeof(glm::mat4), m_Animation->m_BoneTransform.data());
			m_Animation->m_Updated = true;
		}
		void AnimationComponent::Update(float _dt)
		{
			m_DeltaTime = _dt;
			m_CurrentTime += m_Animation->GetTicksPerSecond() * m_DeltaTime;
			m_CurrentTime = fmod(m_CurrentTime, m_Animation->GetDuration());
			ComputeTransform(&m_Animation->GetRootNode(), glm::mat4(1.0f));

			UpdateBuffer();
		}
		Animation* AnimationComponent::GetAnimation()
		{
			return m_Animation;
		}

		void AnimationComponent::ComputeTransform(const AnimNode* _node, glm::mat4 _parent)
		{
			std::string _name = _node->Name;
			glm::mat4 _node_transform = _node->Transform;

			Bone* _bone = m_Animation->FindBone(_name);

			if (_bone)
			{
				_bone->Update(m_CurrentTime);
				_node_transform = _bone->GetLocalTransform();
			}

			glm::mat4 global_transform = _parent * _node_transform;

			DataBlock::BoneMap& bone_info = m_Animation->GetBoneMap();

			if (bone_info.find(_name) != bone_info.end())
			{
				DataBlock::BoneInfo& info = bone_info[_name];
				glm::mat4 _offset = info.Offset;
				m_BoneTransform[info.ID] = global_transform * _offset;
			}

			for (size_t i = 0; i < _node->ChildCount; i++)
				ComputeTransform(&_node->Children[i], global_transform);
		}
	}
}