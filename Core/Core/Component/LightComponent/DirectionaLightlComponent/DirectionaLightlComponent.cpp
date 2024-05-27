#include "DirectionaLightlComponent.h"

namespace OE1Core
{
	namespace Component
	{
		DirectionalLightComponent::DirectionalLightComponent(GLuint _buffer, int _idx)
			: BaseLightComponent{_buffer, _idx}
		{

		}

		DirectionalLightComponent::DirectionalLightComponent(const DirectionalLightComponent& _other, int _idx)
		
			: BaseLightComponent{_other.m_BufferID, _idx}
		{
			m_Light = _other.m_Light;
		}

		DirectionalLightComponent::~DirectionalLightComponent()
		{

		}

		void DirectionalLightComponent::Update(glm::vec3 _position, glm::vec3 _rot)
		{
			m_Light.Position = glm::vec4(_position, 1.0f);
			m_Light.Direction = glm::vec4(_rot, 1.0f);
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
			glBufferSubData(GL_UNIFORM_BUFFER, m_Index * Memory::s_CoreLightPackageBufferSize, Memory::s_CoreLightPackageBufferSize, &m_Light);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
}