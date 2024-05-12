#ifndef OE1_RAY_H_
#define OE1_RAY_H_

#include <glm/glm.hpp>
#include "../Component/CameraComponent/CameraComponent.h"

namespace OE1Core
{
	class Ray
	{
	public:
		Ray(Component::CameraComponent* _camera);
		~Ray();

		glm::vec3 GetRayDirection(float _posX, float posY);
		glm::vec3 GetRayDirection(glm::ivec2 _pos);
		glm::vec3 GetRayDirection(glm::vec2 _pos);
		void SwapCamera(Component::CameraComponent* _camera);


	protected:
		Component::CameraComponent* m_Camera = nullptr;

	protected://Util
		glm::vec2 GetNormalizedCoords(float _posX, float _posY);
		glm::vec4 ToEyeCoord(glm::vec4 _clip_coord);
		glm::vec3 ToWorldCoord(glm::vec4 _eye_coord);

	};
}

#endif // !OE1_RAY_H_
