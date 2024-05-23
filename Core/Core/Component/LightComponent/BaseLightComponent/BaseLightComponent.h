#ifndef OE1_BASE_LIGHT_COMPONENT_H_
#define OE1_BASE_LIGHT_COMPONENT_H_

#include "UniformBlocks.h"

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
			void Update(glm::vec3 _position);
			void UpdateBuffer();
			Memory::CoreLight& GetLight();
			GLuint GetBufferID();


		protected:
			Memory::CoreLight m_Light;
			int m_Index;
			GLuint m_BufferID;

		};
	}
}

#endif // !OE1_BASE_LIGHT_COMPONENT_H_
