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
		void BaseLightComponent::BindBaseLightComponent(lua_State* L)
		{
			using namespace luabridge;

			getGlobalNamespace(L).beginNamespace("Memory")
				.beginClass<Memory::CoreLight>("CoreLight")
					.addData<glm::vec4>("Color", &Memory::CoreLight::Color)
				.endClass()
				.endNamespace()
				.beginClass<BaseLightComponent>("BaseLightComponent")
					.addConstructor<void(*)(GLuint, int)>()
					//.addFunction("SetIndex", &BaseLightComponent::SetIndex)
					.addFunction("GetIndex", &BaseLightComponent::GetIndex)
					//.addFunction("Update", &BaseLightComponent::Update)
					.addFunction("UpdateBuffer", &BaseLightComponent::UpdateBuffer)
					.addFunction("GetData", &BaseLightComponent::GetData)
					//.addFunction("GetBufferID", &BaseLightComponent::GetBufferID)
				.endClass();

			luabridge::push(L, this);
			lua_setglobal(L, "LIGHT");

		}
	}
}