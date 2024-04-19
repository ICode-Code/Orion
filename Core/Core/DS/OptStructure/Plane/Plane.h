#ifndef OE1_OPT_STRUCT_PLANE_H_
#define OE1_OPT_STRUCT_PLANE_H_


#include <glm/glm.hpp>

namespace OE1Core
{
	class Plane
	{
	public:
		Plane() = default;
		Plane(const glm::vec3 p, const glm::vec3 normal);

		glm::vec3 PointOnPlane() const;
		float GetSignedDistanceToPlace(const glm::vec3& _point);

		glm::vec3& GetNormal();
		float GetDistance();

	protected:
		glm::vec3 m_Normal = glm::vec3(0.0f, 1.0f, 0.0f);
		float m_Distance = 0.0f;
	};
}

#endif // !OE1_OPT_STRUCT_PLANE_H_
