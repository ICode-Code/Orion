#ifndef OE1_BASE_QUAD_H_
#define OE1_BASE_QUAD_H_

#include <GL/glew.h>

namespace OE1Core
{
	struct BaseQuad
	{
	public:
		GLuint m_VAO;
		GLuint m_InstanceBuffer;
		GLuint m_VBO;
		GLuint m_EBO;

	public:
		const int m_IndicesCount = 6;
		const float m_QuadVertexData[20] = {
			// positions         texture coords
			 1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
			-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
			-1.0f,  1.0f, 0.0f,  0.0f, 1.0
		};
		const unsigned int m_Indices[6] = {
			0, 1, 3,
			1, 2, 3
		};
	};
}

#endif // !OE1_BASE_QUAD_H_
