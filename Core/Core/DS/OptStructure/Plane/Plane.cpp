#include "Plane.h"

namespace OE1Core
{
	Plane::Plane(const glm::vec3 p, const glm::vec3 normal)
		: m_Normal(glm::normalize(normal)), m_Distance(glm::dot(m_Normal, p))
	{ }

	glm::vec3 Plane::PointOnPlane() const
	{
		return m_Distance * m_Normal;
	}
	float Plane::GetSignedDistanceToPlace(const glm::vec3& _point)
	{
		return glm::dot(m_Normal, _point) - m_Distance;
	}

	glm::vec3& Plane::GetNormal() { return m_Normal; }
	float Plane::GetDistance() { return m_Distance; }
}