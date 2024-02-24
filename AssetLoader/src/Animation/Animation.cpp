#include "Animation.h"


namespace OE1Core
{
	Animation::~Animation()
	{

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
}