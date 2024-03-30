#ifndef OE1_ANIMATION_COMPONENT_H_
#define OE1_ANIMATION_COMPONENT_H_

#include "../Core/CoreAnimation/AnimationManager/AnimationManager.h"
#include "../Common/Shared/UniformBlocks.h"
#include "../Core/CoreAnimation/MemoryBufferLocator.h"

#include "AnimationController/AnimationController.h"
#include <GL/glew.h>
#include <Log.h>

#include <functional>

namespace OE1Core
{
	namespace Component
	{
		class AnimationComponent
		{
			friend class InspectorComponent;
		public:
			AnimationComponent(Animation* _animation, uint32_t _entity, MemoryBufferLocator _buffer_locator);
			~AnimationComponent();


			void SetSkinnedMeshComponentCallback(const std::function<void(int)>& _callback);

			GLintptr GetOffset();
			void SetOffset(GLintptr _offset);
			
			void SetAnimationBufferID(GLuint _id);
			GLuint GetAnimationBufferID();

			void LinkStateMachine();

			// This will only update the buffer
			void UpdateBuffer();

			// This will compute the tranform and update the buffer
			void Update(float _dt);
			Animation* GetAnimation();

			void SwitchAnimation(Animation* _animation);
			void SetAnimation(Animation* _animation);
			void SetUpdateBufferLocator(MemoryBufferLocator _new);
			MemoryBufferLocator GetBufferLocator();
			AnimationController* GetAnimationController();

		private:
			bool m_LinkWithStateMachine = false;
			AnimationController* m_AnimationController = nullptr;
			Animation* m_Animation		= nullptr;
			MemoryBufferLocator m_BufferLocator;
			uint32_t m_EntityID;
			std::function<void(int)> m_SkinnedMeshComponentUpdateCallback;
		};
	}
}

#endif // !OE1_ANIMATION_COMPONENT_H_
