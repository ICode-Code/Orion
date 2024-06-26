#ifndef OE1_BASE_LIGHT_COMPONENT_H_
#define OE1_BASE_LIGHT_COMPONENT_H_

#include "UniformBlocks.h"

#include <Lua/lua.hpp>
#include <LuaBridge/LuaBridge.h>

namespace OE1Core
{
	namespace Component
	{
		class BaseLightComponent
		{
		public:
			BaseLightComponent(GLuint _buffer, int _index);
			~BaseLightComponent();

			void SetIndex(int _index);
			int GetIndex();
			virtual void Update(glm::vec3 _position, glm::vec3 _rot = glm::vec3(-0.2f, -1.0f, -0.3f));
			virtual void UpdateBuffer();
			Memory::CoreLight& GetData();
			GLuint GetBufferID();
			void BindBaseLightComponent(lua_State* L);


		protected:
			Memory::CoreLight m_Light;
			int m_Index;
			GLuint m_BufferID;

		};
	}
}

#endif // !OE1_BASE_LIGHT_COMPONENT_H_
