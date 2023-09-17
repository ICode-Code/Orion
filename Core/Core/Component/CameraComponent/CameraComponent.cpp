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
		void CameraComponent::Update(glm::vec3 _position)
		{
			m_Position		= _position;
			m_Projection	= glm::perspective(glm::radians((float)m_FieldOfView), GetAspectRatio(), m_Near, m_Far);
			m_View			= glm::lookAt(m_Position, m_Position + m_Front, m_Up);
		}
	}
}