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
	namespace Component { class InspectorComponent; class AnimationComponent; }
	class Animation
	{
		friend class Loader::AnimationLoader;
		friend class Component::InspectorComponent;
		friend class Component::AnimationComponent;
	public:
		Animation() = default;
		Animation(size_t _bone_count);
		~Animation();


		float GetTicksPerSecond();
		float GetDuration();
		AnimNode& GetRootNode();
		DataBlock::BoneMap& GetBoneMap();
		Bone* FindBone(std::string _name);
		int GetBoneCount();
		int GetBoneCount() const;
		void SetBoneCount(int _count);
		
		std::string GetName() const;
		std::string GetName();

		void SetName(std::string _name);

		void UpdateTransform(float dt);
		void UpdateBoneTransformBuffer(size_t _size);

		void Play();
		void Pause();
		void Stop();
		

	private:
		float m_DeltaTime = 0.0f;
		float m_CurrentTime = 0.0f;
		std::vector<glm::mat4>	m_BoneTransform;

		int m_BoneCount = 0;
		float m_Duration;
		float m_TickPerSecond;
		std::vector<Bone> m_Bones;
		AnimNode m_RootNode;
		std::string m_Name = "##";
		DataBlock::BoneMap m_BoneMap;

		bool m_Play = false;

		// This are flag we will use to sync the thread if we need to to
		bool m_Computed = false;
		bool m_Updated = false;

	private: // Util
		void ComputeTransform(const AnimNode* _node, glm::mat4 _parent);
	};
}

#endif // !OE1_ANIMATION_H_
