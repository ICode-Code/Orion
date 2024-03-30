#ifndef OE1_ANIMATION_CONTROLLER_H_
#define OE1_ANIMATION_CONTROLLER_H_


#include "Animation/Animation.h"
#include "AnimationState.h"


#include <unordered_map>

namespace OE1Core
{
	namespace Component
	{
		class AnimationController
		{
			friend class AnimationStateMachinePad;
			friend class AnimationComponent;
		public:
			AnimationController(uint32_t _ent);
			~AnimationController();

			void Update();
			bool ValidState(ANIMATION_STATE _state);
			void BindVoidState(ANIMATION_STATE _state, std::string _name);
			void BindState(ANIMATION_STATE _state, Animation* _animation, std::string _name);
			void SetActiveState(ANIMATION_STATE _state);
			void SetDefaultState(ANIMATION_STATE _state); 
			bool ApplyDefaultState();
			bool HasDefaultState();
			ANIMATION_STATE GetActiveAnimationState();

		private:
			std::unordered_map<ANIMATION_STATE, Animation*> m_BindedStateAnimations;
			std::unordered_map<std::string, ANIMATION_STATE> m_BindedStateAnimationName;
			ANIMATION_STATE m_ActiveState = ANIMATION_STATE::T_POS;

			// This is the state which is applyed to a target when no input is detected
			ANIMATION_STATE m_DefaultState = ANIMATION_STATE::T_POS;
			uint32_t m_EntityID;
		};
	}
}

#endif // !OE1_ANIMATION_CONTROLLER_H_
