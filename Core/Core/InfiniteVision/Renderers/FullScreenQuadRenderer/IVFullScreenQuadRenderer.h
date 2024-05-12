#ifndef OE1_IV_FULL_SCREEN_QUAD_RENDERER_H_
#define OE1_IV_FULL_SCREEN_QUAD_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../Core/DS/Quad/Quad.h"


namespace OE1Core
{
	namespace Renderer
	{
		class IVFullScreenQuadRenderer : public IVBaseRenderer
		{
		public:
			IVFullScreenQuadRenderer();
			~IVFullScreenQuadRenderer();

			void Render(GLuint _texture);

		protected:
			
			OE1Core::DS::Quad* m_Quad = nullptr;
		};
	}
}

#endif // !OE1_IV_FULL_SCREEN_QUAD_RENDERER_H_
