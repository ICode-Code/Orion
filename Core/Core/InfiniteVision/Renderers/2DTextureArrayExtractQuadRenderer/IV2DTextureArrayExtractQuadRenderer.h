#ifndef OE1_IV_2D_TEXTURE_ARRAY_EXTRACT_QUAD_RENDERER_H_
#define OE1_IV_2D_TEXTURE_ARRAY_EXTRACT_QUAD_RENDERER_H_

#include "../IVBaseRenderer.h"
#include "../../../SFQuad/SFQuad.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IV2DTextureArrayExtractQuadRenderer : public IVBaseRenderer
		{
		public:
			IV2DTextureArrayExtractQuadRenderer();
			~IV2DTextureArrayExtractQuadRenderer();

			// This will Attach shader
			void Render();
			// This won't Attach Shader
			void RenderX();
			inline Shader* GetShader() const { return m_Shader; }

		protected:
			Shader* m_Shader = nullptr;
			SFQuad* m_Quad = nullptr;
		};
	}
}

#endif // !OE1_IV_2D_TEXTURE_ARRAY_EXTRACT_QUAD_RENDERER_H_
