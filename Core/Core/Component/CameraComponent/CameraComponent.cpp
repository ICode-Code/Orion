#include "CameraComponent.h"


namespace OE1Core
{
	namespace Component
	{
		CameraComponent::CameraComponent()
		{
			m_Position = glm::vec3(0.0f, 0.0f, 0.0f);
			m_Front = glm::vec3(0.0f, 0.0f, -1.0f);
			m_Up = glm::vec3(0.0f, 1.0f, 0.0f);
			m_Right = glm::cross(m_Up, m_Front);
			m_Resolution = glm::vec2(512.0f, 512.0f);
			m_Yaw = -89.0f;
			m_Pitch = 0.0f;
			m_AspectRatio = 1.0f;
		}
		CameraComponent::~CameraComponent()
		{

		}
		bool CameraComponent::ShouldCull()
		{
			return m_Cull;
		}
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