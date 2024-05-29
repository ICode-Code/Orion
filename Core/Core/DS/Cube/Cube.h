#ifndef OE1_CUBE_H_
#define OE1_CUBE_H_

#include <GL/glew.h>



namespace OE1Core
{
	namespace Renderer { class IVSkyboxRenderer; }

	namespace DS
	{
		class Cube
		{
			friend class Renderer::IVSkyboxRenderer;
		public:
			Cube();
			~Cube();

			unsigned int GetVAO();


		private:
			unsigned int m_VAO;
			unsigned int m_VBO;

		private:
			float m_Vertex[288]
				{
					// Coordinate        Texture         Normal
				  -1.0f, -1.0f, -1.0f,	0.0f, 0.0f,	 0.0f, 0.0f, -1.0f,
				   1.0f, -1.0f, -1.0f,	1.0f, 0.0f,	 0.0f, 0.0f, -1.0f,
				   1.0f,  1.0f, -1.0f,	1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,
				   1.0f,  1.0f, -1.0f,	1.0f, 1.0f,	 0.0f, 0.0f, -1.0f,
				  -1.0f,  1.0f, -1.0f,	0.0f, 1.0f,	 0.0f, 0.0f, -1.0f,
				  -1.0f, -1.0f, -1.0f,	0.0f, 0.0f,	 0.0f, 0.0f, -1.0f,

				  -1.0f, -1.0f,  1.0f,	0.0f, 0.0f,	 0.0f, 0.0f,  1.0f,
				   1.0f, -1.0f,  1.0f,	1.0f, 0.0f,	 0.0f, 0.0f,  1.0f,
				   1.0f,  1.0f,  1.0f,	1.0f, 1.0f,	 0.0f, 0.0f,  1.0f,
				   1.0f,  1.0f,  1.0f,	1.0f, 1.0f,	 0.0f, 0.0f,  1.0f,
				  -1.0f,  1.0f,  1.0f,	0.0f, 1.0f,	 0.0f, 0.0f,  1.0f,
				  -1.0f, -1.0f,  1.0f,	0.0f, 0.0f,	 0.0f, 0.0f,  1.0f,

				  -1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 -1.0f, 0.0f,  0.0f,
				  -1.0f,  1.0f, -1.0f,	1.0f, 1.0f,	 -1.0f, 0.0f,  0.0f,
				  -1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 -1.0f, 0.0f,  0.0f,
				  -1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 -1.0f, 0.0f,  0.0f,
				  -1.0f, -1.0f,  1.0f,	0.0f, 0.0f,	 -1.0f, 0.0f,  0.0f,
				  -1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 -1.0f, 0.0f,  0.0f,

				   1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 1.0f, 0.0f,  0.0f,
				   1.0f,  1.0f, -1.0f,	1.0f, 1.0f,	 1.0f, 0.0f,  0.0f,
				   1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 1.0f, 0.0f,  0.0f,
				   1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 1.0f, 0.0f,  0.0f,
				   1.0f, -1.0f,  1.0f,	0.0f, 0.0f,	 1.0f, 0.0f,  0.0f,
				   1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 1.0f, 0.0f,  0.0f,

				  -1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 0.0f, -1.0f,  0.0f,
				   1.0f, -1.0f, -1.0f,	1.0f, 1.0f,	 0.0f, -1.0f,  0.0f,
				   1.0f, -1.0f,  1.0f,	1.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
				   1.0f, -1.0f,  1.0f,	1.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
				  -1.0f, -1.0f,  1.0f,	0.0f, 0.0f,	 0.0f, -1.0f,  0.0f,
				  -1.0f, -1.0f, -1.0f,	0.0f, 1.0f,	 0.0f, -1.0f,  0.0f,

				  -1.0f,  1.0f, -1.0f,	0.0f, 1.0f,	 0.0f, 1.0f,  0.0f,
				   1.0f,  1.0f, -1.0f,	1.0f, 1.0f,	 0.0f, 1.0f,  0.0f,
				   1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 0.0f, 1.0f,  0.0f,
				   1.0f,  1.0f,  1.0f,	1.0f, 0.0f,	 0.0f, 1.0f,  0.0f,
				  -1.0f,  1.0f,  1.0f,	0.0f, 0.0f,	 0.0f, 1.0f,  0.0f,
				  -1.0f,  1.0f, -1.0f,	0.0f, 1.0f,	 0.0f, 1.0f,  0.0f,
				};
		};
	}
}

#endif // !OE1_CUBE_H_
