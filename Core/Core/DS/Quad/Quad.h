#ifndef OE1_QUAD_H_
#define OE1_QUAD_H_

#include <GL/glew.h>

namespace OE1Core
{
	namespace Renderer { class IVFullScreenQuadRenderer; }
	namespace DS
	{
		class Quad
		{
			friend class Renderer::IVFullScreenQuadRenderer;
		public:
			Quad();
			~Quad();


			unsigned int GetVAO();


		private:
			unsigned int m_VAO;
			unsigned int m_VBO;
			unsigned int m_EBO;

		private:
			float m_Vertex[20] = {
				// positions         texture coords
				 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
				 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
				-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
				-1.0f,  1.0f, 0.0f,  0.0f, 1.0f
			};
			const unsigned int m_Indices[6] = {
			0, 1, 3,
			1, 2, 3
			};
		};
	}
}

#endif // !OE1_QUAD_H_
