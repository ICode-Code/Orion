#ifndef OE1_IV_SKYBOX_RENDERER_H_
#define OE1_IV_SKYBOX_RENDERER_H_



#include "../IVBaseRenderer.h"
#include "../Core/DS/Cube/Cube.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVSkyboxRenderer : public IVBaseRenderer
		{
		public:
			IVSkyboxRenderer();
			~IVSkyboxRenderer();

			void Render(GLuint _texture, int _camera_idx = 0);

		protected:
			OE1Core::DS::Cube* m_Cube = nullptr;
		};
	}
}


#endif // !OE1_IV_SKYBOX_RENDERER_H_
