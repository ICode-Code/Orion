#include "Animator.h"


namespace OE1Core
{
	Animator::Animator()
	{
		s_CurrentTime = 0.0f;
		
		s_BoneTransforms.reserve(200);
		
		for (size_t i = 0; i < 200; i++)
			s_BoneTransforms.push_back(glm::mat4(1.0f));
	}
	Animator::~Animator()
	{

	}

	void Animator::UpdateAnimation(float _dt)
	{
		s_DtTime = _dt;
		if (s_CurrentAnimation)
		{
			s_CurrentTime += s_CurrentAnimation->GetTicksPerSecond() * _dt;
			s_CurrentTime = fmod(s_CurrentTime, s_CurrentAnimation->GetDuration());
			ComputeTransform(&s_CurrentAnimation->GetRootNode(), glm::mat4(1.0f));
		}
	}
	void Animator::PlayAnimation(Animation* _animation)
	{
		s_CurrentTime = 0.0f;
		s_CurrentAnimation = _animation;
	}
	void Animator::ComputeTransform(const AnimNode* _node, glm::mat4 _parent)
	{
		std::string _name = _node->Name;
		glm::mat4 _node_transform = _node->Transform;

		Bone* _bone = s_CurrentAnimation->FindBone(_name);

		if (_bone)
		{
			_bone->Update(s_CurrentTime);
			_node_transform = _bone->GetLocalTransform();
		}

		glm::mat4 global_transform = _parent * _node_transform;

		DataBlock::BoneMap& bone_info = s_CurrentAnimation->GetBoneMap();

		if (bone_info.find(_name) != bone_info.end())
		{
			DataBlock::BoneInfo& info = bone_info[_name];
			glm::mat4 _offset = info.Offset;
			s_BoneTransforms[info.ID] = global_transform * _offset;
		}

		for (size_t i = 0; i < _node->ChildCount; i++)
			ComputeTransform(&_node->Children[i], global_transform);
	}

	std::vector<glm::mat4> Animator::GetBonesTransform() { return s_BoneTransforms; }
}