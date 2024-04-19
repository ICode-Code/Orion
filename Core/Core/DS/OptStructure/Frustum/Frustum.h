#ifndef OE1_OPT_STRUCT_FRUSTUM_H_
#define OE1_OPT_STRUCT_FRUSTUM_H_

#include "../Plane/Plane.h"

namespace OE1Core
{
	namespace Component { class CameraComponent; }
	class Frustum
	{
		friend Component::CameraComponent;
	public:
		Frustum() = default;

		Plane& Front();
		Plane& Back();

		Plane& Right();
		Plane& Left();

		Plane& Top();
		Plane& Bottom();


		/// <summary>
		/// Make sure the idx is  0 - 5
		/// </summary>
		/// <param name="_idx"></param>
		/// <returns></returns>
		Plane& GetPlane(int _idx);


	private:
		Plane m_Plane[6];
		glm::vec3 m_Position = glm::vec3(0.0f);
	};
}

#endif // !OE1_OPT_STRUCT_FRUSTUM_H_
