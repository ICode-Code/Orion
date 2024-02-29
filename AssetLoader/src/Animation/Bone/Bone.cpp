#include "Bone.h"


namespace OE1Core
{
	Bone::Bone(std::string _name, int _id, KeyFrameChannel& _channel)
	{
		m_Name = _name;
		m_ID = _id;
		m_LocalTransform = glm::mat4(1.0f);

		m_Positions		= _channel.Positions;		m_PositionCount = _channel.Positions.size();
		m_Rotations		= _channel.Rotations;		m_RotationCount = _channel.Rotations.size();
		m_Scales		= _channel.Scales;			m_ScaleCount	= _channel.Scales.size();
	}
	Bone::~Bone()
	{

	}
	std::string Bone::GetBoneName() const { return m_Name; }
	int Bone::GetBoneID() { return m_ID; }
	glm::mat4 Bone::GetLocalTransform() { return m_LocalTransform; }


	void Bone::Update(float _animation_time)
	{
		glm::mat4 _trans = InterpolatePosition(_animation_time);
		glm::mat4 _rot = InterpolateRotation(_animation_time);
		glm::mat4 _scale = InterpolateScaling(_animation_time);

		m_LocalTransform = _trans * _rot * _scale;
	}


	int Bone::GetPositionIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_PositionCount - 1; i++)
			if (_anim_time < m_Positions[i + 1].TimeStamp)
				return (int)i;

		assert(0);
		return 0;
	}
	int Bone::GetRotationIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_RotationCount - 1; i++)
			if (_anim_time < m_Rotations[i + 1].TimeStamp)
				return (int)i;

		assert(0);
		return 0;
	}
	int Bone::GetScaleIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_ScaleCount - 1; i++)
			if (_anim_time < m_Scales[i + 1].TimeStamp)
				return (int)i;

		assert(0);
		return 0;
	}

	float Bone::GetScaleFactor(float _last, float _next, float _current)
	{
		float _scale_factor = 0.0f;
		float _mid = _current - _last;
		float _diff = _next - _last;
		_scale_factor = _mid / _diff;
		return _scale_factor;
	}
	glm::mat4 Bone::InterpolatePosition(float _anim_time)
	{
		if (m_PositionCount == 1)
			return glm::translate(glm::mat4(1.0f), m_Positions[0].Position);

		int p0 = GetPositionIndex(_anim_time);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(m_Positions[p0].TimeStamp, m_Positions[p1].TimeStamp, _anim_time);

		glm::vec3 _final_pos = glm::mix(m_Positions[p0].Position, m_Positions[p1].Position, _scale_factor);
		
		return glm::translate(glm::mat4(1.0f), _final_pos);
	}
	glm::mat4 Bone::InterpolateRotation(float _anim_time)
	{
		if (m_RotationCount == 1)
			return glm::toMat4(glm::normalize(m_Rotations[0].Rotation));

		int p0 = GetRotationIndex(_anim_time);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(m_Rotations[p0].TimeStamp, m_Rotations[p1].TimeStamp, _anim_time);

		glm::quat _final_rot = glm::slerp(m_Rotations[p0].Rotation, m_Rotations[p1].Rotation, _scale_factor);

		return glm::toMat4(glm::normalize(_final_rot));
	}
	glm::mat4 Bone::InterpolateScaling(float _anim_time)
	{
		if (m_ScaleCount == 1)
			return glm::scale(glm::mat4(1.0f), m_Scales[0].Scale);

		int p0 = GetScaleIndex(_anim_time);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(m_Scales[p0].TimeStamp, m_Scales[p1].TimeStamp, _anim_time);

		glm::vec3 _final_size = glm::mix(m_Scales[p0].Scale, m_Scales[p1].Scale, _scale_factor);

		return glm::scale(glm::mat4(1.0f), _final_size);
	}

}