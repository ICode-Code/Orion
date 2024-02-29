#ifndef OE1_ANIMATION_COMPONENT_H_
#define OE1_ANIMATION_COMPONENT_H_


#include "Animation/Animation.h"
#include <GL/glew.h>
#include <Log.h>


namespace OE1Core
{
	namespace Component
	{
		class AnimationComponent
		{
			friend class InspectorComponent;
		public:
			AnimationComponent(Animation* _animation, GLintptr _offset, GLuint _animation_buffer);
			~AnimationComponent();

			GLintptr GetOffset();
			void SetOffset(GLintptr _offset);

			void SetAnimationBufferID(GLuint _id);
			GLuint GetAnimationBufferID();

			// This will only update the buffer
			void UpdateBuffer();

			// This will compute the tranform and update the buffer
			void Update(float _dt);
			Animation* GetAnimation();

		private:
			Animation* m_Animation		= nullptr;


			GLintptr m_Offset			= -1;
			GLuint m_AnimationBuffer	= -1;

			// we don't use this but in case if we want to compute it  right here and now
			// we can use it
			std::vector<glm::mat4>		m_BoneTransform;
			float m_CurrentTime = 0.0f;
			float m_DeltaTime = 0.0f;


		protected:
			void ComputeTransform(const AnimNode* _node, glm::mat4 _parent);
		};
	}
}

#endif // !OE1_ANIMATION_COMPONENT_H_
