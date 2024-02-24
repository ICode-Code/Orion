#ifndef OE1_BONE_H_
#define OE1_BONE_H_

#include "../AnimNode.h"
#include <glm/gtx/quaternion.hpp>

namespace OE1Core
{
	class Bone
	{
	public:
		Bone(std::string name, int ID, KeyFrameChannel& _channels);
		~Bone();

		std::string GetBoneName() const;
		int GetBoneID();
		glm::mat4 GetLocalTransform();
		void Update(float _animation_time);

		int GetPositionIndex(float _anim_time);
		int GetRotationIndex(float _anim_time);
		int GetScaleIndex(float _anim_time);

	private:
		float GetScaleFactor(float _last, float _next, float _current);
		glm::mat4 InterpolatePosition(float _anim_time);
		glm::mat4 InterpolateRotation(float _anim_time);
		glm::mat4 InterpolateScaling(float _anim_time);

	private:
		std::vector<KeyPosition> m_Positions; size_t m_PositionCount;
		std::vector<KeyRotation> m_Rotations; size_t m_RotationCount;
		std::vector<KeyScale> m_Scales; size_t m_ScaleCount;

		glm::mat4 m_LocalTransform;
		std::string m_Name;
		int m_ID;
	};
}

#endif // !OE1_BONE_H_
