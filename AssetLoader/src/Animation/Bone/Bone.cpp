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
	bool Bone::OnTransition() { return m_OnTransition; }
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
	void Bone::Interpolate(Bone& _bone, float _animation_time, float _time)
	{
		glm::mat4 _trans	=	InterpolatePositionToPosition(_bone, _animation_time, _time);
		glm::mat4 _rot		=	InterpolateRotationToToRotation(_bone, _animation_time, _time);
		glm::mat4 _scale	=	InterpolateScalingToScale(_bone, _animation_time, _time);

		m_LocalTransform = _trans * _rot * _scale;
	}


	int Bone::GetPositionIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_PositionCount - 1; i++)
			if (_anim_time < m_Positions[i + 1].TimeStamp)
				return (int)i;

		return 0;
	}
	int Bone::GetRotationIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_RotationCount - 1; i++)
			if (_anim_time < m_Rotations[i + 1].TimeStamp)
				return (int)i;

		return 0;
	}
	int Bone::GetScaleIndex(float _anim_time)
	{
		for (size_t i = 0; i < m_ScaleCount - 1; i++)
			if (_anim_time < m_Scales[i + 1].TimeStamp)
				return (int)i;

		return 0;
	}

	int Bone::GetPositionIndex(float _anim_time, std::vector<KeyPosition>& _pos)
	{
		for (size_t i = 0; i < _pos.size() - 1; i++)
			if (_anim_time < _pos[i + 1].TimeStamp)
				return (int)i;

		return 0;
	}
	int Bone::GetRotationIndex(float _anim_time, std::vector<KeyRotation>& _rot)
	{
		for (size_t i = 0; i < _rot.size() - 1; i++)
			if (_anim_time < _rot[i + 1].TimeStamp)
				return (int)i;

		return 0;
	}
	int Bone::GetScaleIndex(float _anim_time, std::vector<KeyScale>& _scale)
	{
		for (size_t i = 0; i < _scale.size() - 1; i++)
			if (_anim_time < _scale[i + 1].TimeStamp)
				return (int)i;

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


	glm::mat4 Bone::InterpolatePositionToPosition(Bone& _bone, float _anim_time, float _duration)
	{
		if (m_PositionCount == 1)
			return glm::translate(glm::mat4(1.0f), m_Positions[0].Position);

		glm::vec3 a =  GetFinalPosition(m_Positions, _anim_time);
		glm::vec3 b = GetFinalPosition(_bone.m_Positions, _anim_time);

		glm::vec3 inter_pos = glm::mix(a, b, _duration);

		return glm::translate(glm::mat4(1.0f), inter_pos);
	}
	glm::mat4 Bone::InterpolateRotationToToRotation(Bone& _bone, float _anim_time, float _duration)
	{
		if (m_RotationCount == 1)
			return glm::toMat4(glm::normalize(m_Rotations[0].Rotation));


		glm::quat a = GetFinalRotation(m_Rotations, _anim_time);
		glm::quat b = GetFinalRotation(_bone.m_Rotations, _anim_time);

		glm::quat inter_rot = glm::slerp(a, b, _duration);

		return glm::toMat4(glm::normalize(inter_rot));
	}
	glm::mat4 Bone::InterpolateScalingToScale(Bone& _bone, float _anim_time, float _duration)
	{
		if (m_ScaleCount == 1)
			return glm::scale(glm::mat4(1.0f), m_Scales[0].Scale);

		glm::vec3 a = GetFinalScale(m_Scales, _anim_time);
		glm::vec3 b = GetFinalScale(_bone.m_Scales, _anim_time);

		glm::vec3 inter_scale = glm::mix(a, b, _duration);

		return glm::scale(glm::mat4(1.0f), inter_scale);
	}

	glm::vec3 Bone::GetFinalPosition(std::vector<KeyPosition>& _pos, float _time)
	{
		int p0 = GetPositionIndex(_time, _pos);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(_pos[p0].TimeStamp, _pos[p1].TimeStamp, _time);
		glm::vec3 _final_pos = glm::mix(_pos[p0].Position, _pos[p1].Position, _scale_factor);

		return _final_pos;
	}
	glm::vec3 Bone::GetFinalScale(std::vector<KeyScale>& _scale, float _time)
	{
		int p0 = GetScaleIndex(_time, _scale);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(_scale[p0].TimeStamp, _scale[p1].TimeStamp, _time);
		glm::vec3 _final_pos = glm::mix(_scale[p0].Scale, _scale[p1].Scale, _scale_factor);

		return _final_pos;
	}
	glm::quat Bone::GetFinalRotation(std::vector<KeyRotation>& _rot, float _time)
	{
		int p0 = GetRotationIndex(_time, _rot);
		int p1 = p0 + 1;

		float _scale_factor = GetScaleFactor(_rot[p0].TimeStamp, _rot[p1].TimeStamp, _time);

		glm::quat _final_rot = glm::slerp(_rot[p0].Rotation, _rot[p1].Rotation, _scale_factor);

		return _final_rot;
	}

}