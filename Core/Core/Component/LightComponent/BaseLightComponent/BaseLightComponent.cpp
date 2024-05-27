#include "BaseLightComponent.h"


namespace OE1Core
{
	namespace Component
	{
		BaseLightComponent::BaseLightComponent(GLuint _buffer, int _index)
		{
			m_BufferID = _buffer;
			m_Index = _index;
		}
		BaseLightComponent::~BaseLightComponent()
		{

		}
		GLuint BaseLightComponent::GetBufferID() { return m_BufferID; };

		Memory::CoreLight& BaseLightComponent::GetData() { return m_Light; };

		void BaseLightComponent::SetIndex(int _index)
		{
			m_Index = _index;
		}
		int BaseLightComponent::GetIndex() { return m_Index; }

		void BaseLightComponent::Update(glm::vec3 _position, glm::vec3 _rot)
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