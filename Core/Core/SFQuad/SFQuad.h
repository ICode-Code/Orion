#ifndef OE1_SFQUAD_H_
#define OE1_SFQUAD_H_

#include <GL/glew.h>

namespace OE1Core
{
	class SFQuad
	{
	public:
		SFQuad();
		~SFQuad();

		void Render(GLuint _texture);
		void Render();
		GLuint m_VAO;

	protected:
		GLuint m_VBO;
		GLuint m_EBO;
		const float m_QuadVertexData[20] = {
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

	protected: // Util
		void Init();
	};
}


#endif // !OE1_SFQUAD_H_
