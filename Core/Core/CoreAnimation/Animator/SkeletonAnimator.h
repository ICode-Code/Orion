#ifndef OE1_ANIMATOR_H_
#define OE1_ANIMATOR_H_

#include "../src/Animation/Animation.h"
#include <chrono>

namespace OE1Core
{
	namespace Component { class AnimationController; }
	class SkeletonAnimator
	{
		friend class PreferenceWin;
		friend class AnimationManager;
		friend class Component::AnimationController;
	public:
		SkeletonAnimator();
		~SkeletonAnimator();

		static void UpdateAnimations(float _dt);

	private:

		static bool HasAnimation(uint32_t _id);
		static void RegisterAnimation(uint32_t _id, Animation* _animation);
		static Animation* GetAnimation(uint32_t _id);
		static void PurgeAnimation(uint32_t _id);
		static int GetActiveAnimationCount();

		inline static float s_FixedUpdateStep = 1.0f/24.0f;
		inline static std::chrono::steady_clock::time_point s_LastUpdateTime = std::chrono::steady_clock::now();
		inline static float s_TimeAccumulation = 0.0f;
		inline static std::unordered_map<uint32_t, Animation*> s_AnimationSet;
	};
}

#endif // !OE1_ANIMATOR_H_
