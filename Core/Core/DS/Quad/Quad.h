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

		private:
			float m_Vertex[30] = {
				// positions   // texCoords
				 -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
				 -1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
				  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,

				 -1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
				  1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
				  1.0f,  1.0f, 0.0f,  1.0f, 1.0f
			};
		};
	}
}

#endif // !OE1_QUAD_H_
