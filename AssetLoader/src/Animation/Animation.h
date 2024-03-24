#ifndef OE1_ANIMATION_H_
#define OE1_ANIMATION_H_

#include "AnimNode.h"
#include "Bone/Bone.h"

#include <glm/gtx/matrix_decompose.hpp>
#include <algorithm>
#include <functional>

namespace OE1Core
{
	namespace Loader
	{
		class AnimationLoader;
	}
	namespace Component { class InspectorComponent; class AnimationComponent; }


	typedef std::function<void(std::string, uint32_t)> ANIMATION_SWITCH_COMMAND_CREATOR_CALLBACK;

	class Animation
	{
		friend class Loader::AnimationLoader;
		friend class Component::InspectorComponent;
		friend class Component::AnimationComponent;
		friend class SkeletonAnimator;
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
		bool& OnTransition();
		
		std::string GetName() const;
		std::string GetName();

		void SetName(std::string _name);

		void SetNextAnimation(Animation* _animation, uint32_t _id);
		/// <summary>
		/// Make Sure to set next animation before calling this
		/// </summary>
		/// <param name="_next_animation"></param>
		/// <param name="_dt"></param>
		/// <param name="_time"></param>
		void Interpolate(float _dt);
		bool IsLastPos(float _dt);

		void UpdateTransform(float dt);
		void UpdateBoneTransformBuffer(size_t _size);
		
		void SetHardCut(bool _val);
		bool GetHardCut();

		void Play();
		void Pause();
		void Stop();

		// Callbacks
		void RegisterAnimationSetCallback(const ANIMATION_SWITCH_COMMAND_CREATOR_CALLBACK& _callback);
		bool HasValidAnimationSetCallback();
		

	private:
		float m_DeltaTime = 0.0f;
		float m_CurrentTime = 0.0f;
		std::vector<glm::mat4>	m_BoneTransform;
		float m_DeltaFactor = 1.0f;


		uint32_t m_TransitionEntityID;
		int m_BoneCount = 0;
		float m_Duration;
		float m_TickPerSecond;
		std::vector<Bone> m_Bones;
		AnimNode m_RootNode;
		std::string m_Name = "##";
		DataBlock::BoneMap m_BoneMap;
		bool m_HasIssues = false;

		bool m_Play = false;

		// This are flag we will use to sync the thread if we need to to
		bool m_Computed = false;
		bool m_Updated = false;

		bool m_OnTransition = false;
		float m_TransitionTime = 0.0f;
		float m_TransitionDuration = 0.15f;
		bool m_LockTranstion = false;
		bool m_HardCut = false;
		
		Animation* m_NextAnimation = nullptr;

	private: // Util
		void ComputeTransform(const AnimNode* _node, glm::mat4 _parent);
		void ComputeTransformTransition(const AnimNode* _node, glm::mat4 _parent, Animation* _other, float _time);
		ANIMATION_SWITCH_COMMAND_CREATOR_CALLBACK m_AnimationSwitchCallback;
		bool m_ValidAnimSetCallback = false;
	};
}

#endif // !OE1_ANIMATION_H_
