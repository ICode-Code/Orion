#ifndef OE1_BONE_H_
#define OE1_BONE_H_

#include "../AnimNode.h"
#include <glm/gtx/quaternion.hpp>
#include <algorithm>

namespace OE1Core
{
	namespace Component { class InspectorComponent; }
	class Bone
	{
		friend class Component::InspectorComponent;
	public:
		Bone(std::string name, int ID, KeyFrameChannel& _channels);
		~Bone();

		bool OnTransition();
		std::string GetBoneName() const;
		int GetBoneID();
		glm::mat4 GetLocalTransform();
		void Update(float _animation_time);

		void Interpolate(Bone& _bone, float _animation_time, float _time);

		int GetPositionIndex(float _anim_time);
		int GetRotationIndex(float _anim_time);
		int GetScaleIndex(float _anim_time);

		int GetPositionIndex(float _anim_time, std::vector<KeyPosition>& _pos);
		int GetRotationIndex(float _anim_time, std::vector<KeyRotation>& _rot);
		int GetScaleIndex(float _anim_time, std::vector<KeyScale>& _scale);

	private:
		float GetScaleFactor(float _last, float _next, float _current);

		glm::mat4 InterpolatePosition(float _anim_time);
		glm::mat4 InterpolateRotation(float _anim_time);
		glm::mat4 InterpolateScaling(float _anim_time);

		glm::mat4 InterpolatePositionToPosition(Bone& _bone, float _anim_time, float _duration);
		glm::mat4 InterpolateRotationToToRotation(Bone& _bone, float _anim_time, float _duration);
		glm::mat4 InterpolateScalingToScale(Bone& _bone, float _anim_time, float _duration);

	private:
		std::vector<KeyPosition> m_Positions; size_t m_PositionCount;
		std::vector<KeyRotation> m_Rotations; size_t m_RotationCount;
		std::vector<KeyScale> m_Scales; size_t m_ScaleCount;

		glm::mat4 m_LocalTransform;
		std::string m_Name;
		int m_ID;
		float m_TranstionTime = 0.0f;
		bool m_OnTransition = false;


	protected:
		glm::vec3 GetFinalPosition(std::vector<KeyPosition>& _pos, float _time);
		glm::vec3 GetFinalScale(std::vector<KeyScale>& _scale, float _time);
		glm::quat GetFinalRotation(std::vector<KeyRotation>& _rot, float _time);
	};
}

#endif // !OE1_BONE_H_
