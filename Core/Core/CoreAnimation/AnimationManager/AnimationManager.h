#ifndef OE1_ANIMATION_MANAGER_H_
#define OE1_ANIMATION_MANAGER_H_

#include "../Animator/SkeletonAnimator.h"
#include "../MemoryBufferLocator.h"

#include "UniformBuffer/UniformBlockManager.h"

namespace OE1Core
{
	class AnimationStateMachinePad;
	class AnimationManager
	{
	public:
		AnimationManager();
		~AnimationManager();

		static void AnimationSwitchCommandCreateHandler(std::string _animation_name, uint32_t _entity_id);
		static void HardSwitch(Animation* _animation, uint32_t _id);
		static void UpdateAnimation(Animation* _animation, uint32_t _id);
		static MemoryBufferLocator RegisterAnimationInstance(Animation* _animation, uint32_t _entity_id);
		static bool HasAnimation(uint32_t _id);
		static Animation* GetAnimation(uint32_t _id);

		static std::unordered_map<std::string, AnimationStateMachinePad*>& GetStateMachineWins();
		static bool RegisterStateMachineWindow(std::string _name, AnimationStateMachinePad* _pad);
		static bool PurgeStateMachineWindow(std::string _name);


	private:
		inline static std::unordered_map<std::string, AnimationStateMachinePad*> s_StateMachineWindows;
		inline static std::vector<Memory::UniformBuffer> s_AnimationUniformBuffer;
		inline static Memory::UniformBuffer* s_AnimationBuffer;
		inline static size_t s_LastEndOffset = 0;
	private: // Util
		/// <summary>
		/// Number of animation that are active in the scene
		/// </summary>
		inline static int s_ActiveAnimation = 0;
	};
}

#endif // !OE1_ANIMATION_MANAGER_H_
