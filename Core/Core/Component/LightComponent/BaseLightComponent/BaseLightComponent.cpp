#include "BaseLightComponent.h"


namespace OE1Core
{
	namespace Component
	{
		BaseLightComponent::BaseLightComponent(GLuint _buffer, int _index)
		{
			m_BufferID = _buffer;
			m_Index = _index;

			m_Light.Position = glm::vec4(0.0f, 5.0f, 0.0f, 0.0f);
			m_Light.Intensity = 5.0f;
			m_Light.Color = glm::vec4(1.0f);
			m_Light.AffectWorld = true;
		}
		BaseLightComponent::~BaseLightComponent()
		{

		}
		GLuint BaseLightComponent::GetBufferID() { return m_BufferID; };

		Memory::CoreLight& BaseLightComponent::GetLight() { return m_Light; };

		void BaseLightComponent::SetIndex(int _index)
		{
			m_Index = _index;
		}
		int BaseLightComponent::GetIndex() { return m_Index; }

		void BaseLightComponent::Update(glm::vec3 _position)
		{
			m_Light.Position = glm::vec4(_position, 1.0f);
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
			glBufferSubData(GL_UNIFORM_BUFFER, m_Index * Memory::s_CoreLightPackageBufferSize, Memory::s_CoreLightPackageBufferSize, &m_Light);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		void BaseLightComponent::UpdateBuffer()
		{
			glBindBuffer(GL_UNIFORM_BUFFER, m_BufferID);
			glBufferSubData(GL_UNIFORM_BUFFER, m_Index * Memory::s_CoreLightPackageBufferSize, Memory::s_CoreLightPackageBufferSize, &m_Light);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
}