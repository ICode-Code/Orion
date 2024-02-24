#ifndef OE1_ANIMATOR_H_
#define OE1_ANIMATOR_H_

#include "../src/Animation/Animation.h"


namespace OE1Core
{
	class Animator
	{
	public:
		Animator();
		~Animator();

		static void UpdateAnimation(float _dt);
		static void PlayAnimation(Animation* _animation);
		static void ComputeTransform(const AnimNode* _node, glm::mat4 _parent);

		static std::vector<glm::mat4> GetBonesTransform();

	private:
		inline static Animation* s_CurrentAnimation = nullptr;
		inline static std::vector<glm::mat4> s_BoneTransforms;
		inline static float s_CurrentTime;
		inline static float s_DtTime;

	};
}

#endif // !OE1_ANIMATOR_H_
