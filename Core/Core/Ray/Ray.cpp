#include "Ray.h"


namespace OE1Core
{
	Ray::Ray(CameraPackage* _camrea_pkg)
	{
		m_CamreaPackage = _camrea_pkg;
	}
	Ray::~Ray()
	{

	}
	glm::vec3 Ray::GetRayDirection(glm::ivec2 _pos)
	{
		return GetRayDirection((float)_pos.x, (float)_pos.y);
	}
	glm::vec3 Ray::GetRayDirection(glm::vec2 _pos)
	{
		return GetRayDirection(_pos.x, _pos.y);
	}
	glm::vec3 Ray::GetRayDirection(float _posX, float _posY)
	{
		glm::vec2 normalize_coord = GetNormalizedCoords(_posX, _posY);
		glm::vec4 clip_coord = glm::vec4(normalize_coord, -1.0f, 1.0f);
		glm::vec4 eye_coord = ToEyeCoord(clip_coord);
		return ToWorldCoord(eye_coord);
	}
	glm::vec2 Ray::GetNormalizedCoords(float _posX, float _posY)
	{
		glm::vec2 res = m_CamreaPackage->GetCamera()->GetResolution();
		float x = (2.0f * _posX) / res.x - 1;
		float y = (2.0f * _posY) / res.y - 1;
		return glm::vec2(x, y);
	}
	glm::vec4 Ray::ToEyeCoord(glm::vec4 _clip_coord)
	{
		glm::vec4 eye_coord = glm::inverse(m_CamreaPackage->GetCamera()->m_Projection) * _clip_coord;
		return glm::vec4(eye_coord.x, eye_coord.y, -1.0f, 0.0f);
	}
	glm::vec3 Ray::ToWorldCoord(glm::vec4 _eye_coord)
	{
		glm::vec4 world = glm::inverse(m_CamreaPackage->GetCamera()->m_View) * _eye_coord;
		return glm::normalize(glm::vec3(world));
	}
}