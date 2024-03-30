#include "Animation.h"


namespace OE1Core
{
	Animation::Animation(size_t _bone_count)
	{
		UpdateBoneTransformBuffer(_bone_count);
		m_TransitionDuration = 0.0001f;
		m_HardCut = true;
	}
	Animation::~Animation()
	{

	}
	void Animation::UpdateBoneTransformBuffer(size_t _size)
	{
		m_BoneTransform.resize(_size);
		for (size_t i = 0; i < _size; i++)
			m_BoneTransform[i] = glm::mat4(1.0f);
	}
	float Animation::GetTicksPerSecond() { return m_TickPerSecond; }
	float Animation::GetDuration() { return m_Duration; }
	AnimNode& Animation::GetRootNode() { return m_RootNode; }
	DataBlock::BoneMap& Animation::GetBoneMap() { return m_BoneMap; }

	Bone* Animation::FindBone(std::string _name)
	{
		auto iter = std::find_if(m_Bones.begin(), m_Bones.end(), [&](const Bone& _bone)
			{
				return _bone.GetBoneName() == _name;
			});

		if (iter == m_Bones.end()) 
			return nullptr;

		return &(*iter);
		
	}
	std::string Animation::GetName() const
	{
		return m_Name;
	}
	std::string Animation::GetName()
	{
		return m_Name;
	}
	void Animation::SetName(std::string _name)
	{
		if (_name.empty())
		{
			m_Name = "Untitled Animation";
			return;
		}
		m_Name = _name;
	}
	int Animation::GetBoneCount()
	{
		return m_BoneCount;
	}
	int Animation::GetBoneCount() const
	{
		return m_BoneCount;
	}
	bool& Animation::OnTransition()
	{
		return m_OnTransition;
	}
	void Animation::SetBoneCount(int _bone_Count)
	{
		m_BoneCount = _bone_Count;
	}
	void Animation::Play() { m_Play = true; }
	void Animation::Pause() { m_Play = false; }
	void Animation::Stop()
	{ 
		m_CurrentTime = 0.0f; 
		m_Play = false; 
	}
	void Animation::UpdateTransform(float dt)
	{
		if (m_Updated)
			return;
		m_DeltaTime = dt * m_DeltaFactor;
		m_CurrentTime += m_TickPerSecond * m_DeltaTime;
		m_CurrentTime = fmod(m_CurrentTime, m_Duration);
		ComputeTransform(&m_RootNode, glm::mat4(1.0f));

		m_Updated = true;
	}
	void Animation::SetHardCut(bool _val)
	{
		m_HardCut = _val;
	}
	bool Animation::GetHardCut()
	{
		return m_HardCut;
	}
	void Animation::ComputeTransform(const AnimNode* _node, glm::mat4 _parent)
	{
		std::string _name = _node->Name;
		glm::mat4 _node_transform = _node->Transform;

		Bone* _bone = FindBone(_name);

		if (_bone)
		{
			
			_bone->Update(m_CurrentTime);
			_node_transform = _bone->GetLocalTransform();
		}

		glm::mat4 global_transform = _parent * _node_transform;

		DataBlock::BoneMap& bone_info = GetBoneMap();

		if (bone_info.find(_name) != bone_info.end())
		{
			DataBlock::BoneInfo& info = bone_info[_name];
			glm::mat4 _offset = info.Offset;
			m_BoneTransform[info.ID] = global_transform * _offset;
		}

		for (size_t i = 0; i < _node->ChildCount; i++)
			ComputeTransform(&_node->Children[i], global_transform);
	}

	void Animation::ComputeTransformTransition(const AnimNode* _node, glm::mat4 _parent, Animation* _other, float _time)
	{
		std::string _name = _node->Name;
		glm::mat4 _node_transform = _node->Transform;

		Bone* _bone = FindBone(_name);
		Bone* _boneB = _other->FindBone(_name);

		if (_bone && _boneB)
		{
			_bone->Interpolate(*_boneB, m_CurrentTime, _time);
			_node_transform = _bone->GetLocalTransform();
		}

		glm::mat4 global_transform = _parent * _node_transform;

		DataBlock::BoneMap& bone_info = GetBoneMap();

		if (bone_info.find(_name) != bone_info.end())
		{
			DataBlock::BoneInfo& info = bone_info[_name];
			glm::mat4 _offset = info.Offset;
			m_BoneTransform[info.ID] = global_transform * _offset;
		}

		for (size_t i = 0; i < _node->ChildCount; i++)
			ComputeTransformTransition(&_node->Children[i], global_transform, _other, _time);
	}
	void Animation::SetNextAnimation(Animation* _animation, uint32_t _id)
	{
		if (m_OnTransition || m_Name == _animation->GetName())
			return;
		
		m_Name = _animation->GetName();
		m_TransitionEntityID = _id;
		m_NextAnimation = _animation;
		m_OnTransition = true;

	}
	void Animation::Interpolate(float _dt)
	{
		if (m_Updated)
			return;

		m_DeltaTime = _dt * m_DeltaFactor;
		m_CurrentTime += m_TickPerSecond * m_DeltaTime;
		m_CurrentTime = fmod(m_CurrentTime, m_Duration);

		if (m_HardCut)
			m_LockTranstion = true;

		if (!IsLastPos(m_CurrentTime) && !m_LockTranstion)
		{
			ComputeTransform(&m_RootNode, glm::mat4(1.0f));
			m_Updated = true;
		}
		else {

			m_LockTranstion = true;

			// Ensure time is within valid range [0, 1]
			m_TransitionTime = std::clamp(m_TransitionTime + m_DeltaTime, 0.0f, m_TransitionDuration);

			// Compute the interpolation factor based on the transition progress
			float _time = m_TransitionTime / m_TransitionDuration;

			ComputeTransformTransition(&m_RootNode, glm::mat4(1.0f), m_NextAnimation, _time);

			if (m_TransitionTime >= m_TransitionDuration)
			{
				m_TransitionTime = 0.0f;


				// Copy the next animtion data
			//	m_HardCut = m_NextAnimation->m_HardCut;
				m_Duration = m_NextAnimation->m_Duration; 
				m_TickPerSecond = m_NextAnimation->m_TickPerSecond;
				m_Bones = m_NextAnimation->m_Bones;
				m_BoneMap = m_NextAnimation->m_BoneMap;
				
				//m_HardCut = m_NextAnimation->m_HardCut;
				// start from the begining
				m_CurrentTime = 0.0f;

				// and no pending next animtion
				m_NextAnimation = nullptr;

				m_LockTranstion = false;

				// We are no longer in transtion mode
				m_OnTransition = false;

			}
			m_Updated = true;
		}
	}
	bool Animation::IsLastPos(float _anim_time)
	{
		for (size_t i = 0; i < m_Bones.size(); i++)
		{
			if ((m_Bones[i].GetPositionIndex(_anim_time) + 1) != (m_Bones[i].m_PositionCount - 1))
				return false;
			if ((m_Bones[i].GetRotationIndex(_anim_time) + 1) != (m_Bones[i].m_RotationCount-1))
				return false;
			if ((m_Bones[i].GetScaleIndex(_anim_time) + 1) != (m_Bones[i].m_ScaleCount-1))
				return false;
		}

		return true;
	}
	void Animation::RegisterAnimationSetCallback(const ANIMATION_SWITCH_COMMAND_CREATOR_CALLBACK& _animation_callback)
	{
		m_AnimationSwitchCallback = _animation_callback;
		m_ValidAnimSetCallback = true;
	}
	bool Animation::HasValidAnimationSetCallback()
	{
		return m_ValidAnimSetCallback;
	}
}