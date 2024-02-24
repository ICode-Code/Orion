#ifndef OE1_ANIMATION_H_
#define OE1_ANIMATION_H_

#include "AnimNode.h"
#include "Bone/Bone.h"


namespace OE1Core
{
	namespace Loader
	{
		class AnimationLoader;
	}
	class Animation
	{
		friend class Loader::AnimationLoader;
	public:
		Animation() = default;
		~Animation();


		float GetTicksPerSecond();
		float GetDuration();
		AnimNode& GetRootNode();
		DataBlock::BoneMap& GetBoneMap();
		Bone* FindBone(std::string _name);
		

	private:
		float m_Duration;
		float m_TickPerSecond;
		std::vector<Bone> m_Bones;
		AnimNode m_RootNode;
		DataBlock::BoneMap m_BoneMap;
	};
}

#endif // !OE1_ANIMATION_H_
