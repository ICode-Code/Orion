#include "CameraComponent.h"


namespace OE1Core
{
	namespace Component
	{
		CameraComponent::CameraComponent()
		{
			m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
			m_Front = glm::vec3(-0.775104523f, -0.631757855f, 0.00974634290f);
			m_Up = glm::vec3(-0.631707966f, 0.775165856f, 0.00794324186f);
			m_Right = glm::vec3(-0.0125732366f, 0.0f, -0.999920905f);//glm::cross(m_Up, m_Front);
			m_Resolution = glm::vec2(512.0f, 512.0f);
			m_Yaw = -180.0f;
			m_Pitch = -40.0f;
			m_AspectRatio = 1.0f;
			m_Cull = true;
		}
		CameraComponent::~CameraComponent()
		{

		}
		bool CameraComponent::ShouldCull()
		{
			return m_Cull;
		}
		void CameraComponent::SetPitch(float _pitch) { m_Pitch = _pitch; }
		void CameraComponent::SetYaw(float _yaw) { m_Yaw = _yaw; }

		float CameraComponent::GetPitch() const { return m_Pitch; };
		float CameraComponent::GetYaw() const { return m_Yaw; };

		glm::vec3 CameraComponent::GetPosition() const { return m_Position; }
		void CameraComponent::SetResolution(glm::vec2 _res)
		{
			m_Resolution = _res;
		}
		float CameraComponent::GetAspectRatio()
		{
			return m_AspectRatio = m_Resolution.x / m_Resolution.y;
		}
		glm::vec2 CameraComponent::GetResolution() { return m_Resolution; }
		void CameraComponent::Update(glm::vec3 _position)
		{
			m_Position		= _position;
			m_Projection	= glm::perspective(glm::radians((float)m_FieldOfView), GetAspectRatio(), m_Near, m_Far);
			m_View			= glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}
		void CameraComponent::Update(glm::vec3 _position, glm::vec3 _target_position)
		{
			m_Position = _position;
			m_Projection = glm::perspective(glm::radians((float)m_FieldOfView), GetAspectRatio(), m_Near, m_Far);
			m_View = glm::lookAt(m_Position, _target_position, m_WorldUp);
		}
		std::vector<glm::vec3>& CameraComponent::GetFrustumCorner()
		{
			m_FrustumCorner.clear();

			float half_field_of_view = glm::radians((float)m_FieldOfView) * 0.5f;

			float near_face_height = 2 * tan(half_field_of_view) * m_Near;
			float near_face_width = near_face_height * GetAspectRatio();

			float far_face_height = 2 * tan(half_field_of_view) * m_Far;
			float far_face_width = far_face_height * GetAspectRatio();

			glm::vec3 NearFace = m_Position + m_Front * m_Near;
			glm::vec3 FarFace = m_Position + m_Front * m_Far;


			// Near face
			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));


			// Far face
			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));


			// Connecting edges
			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) - (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) - (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace - (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace - (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));

			m_FrustumCorner.push_back((NearFace + (m_Up * near_face_height / 2.0f) + (m_Right * near_face_width / 2.0f)));
			m_FrustumCorner.push_back((FarFace + (m_Up * far_face_height / 2.0f) + (m_Right * far_face_width / 2.0f)));

			return m_FrustumCorner;
		}
		Frustum& CameraComponent::GetFrustum()
		{
			const float halfVSide = m_Far * tanf(glm::radians((float)m_FieldOfView) * 0.5f);
			const float halfHSide = halfVSide * GetAspectRatio();
			const glm::vec3 frontMultFar = m_Far * m_Front;

			m_Frustum.m_Position = m_Position;

			// Front
			m_Frustum.m_Plane[0] = Plane(m_Position + m_Near * m_Front, m_Front);

			// Back
			m_Frustum.m_Plane[1] = Plane(m_Position + frontMultFar, -m_Front);

			// Right
			m_Frustum.m_Plane[2] = Plane(m_Position, glm::cross(frontMultFar - m_Right * halfHSide, m_Up));

			// Left
			m_Frustum.m_Plane[3] = Plane(m_Position, glm::cross(m_Up, frontMultFar + m_Right * halfHSide));

			// Top
			m_Frustum.m_Plane[4] = Plane(m_Position, glm::cross(m_Right, frontMultFar - m_Up * halfVSide));

			// Bottom
			m_Frustum.m_Plane[5] = Plane(m_Position, glm::cross(frontMultFar + m_Up * halfVSide, m_Right));

			return m_Frustum;
		}
	}
}