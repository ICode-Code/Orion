#include "IV2DTextureArrayExtractQuadRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IV2DTextureArrayExtractQuadRenderer::IV2DTextureArrayExtractQuadRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::TEXTURE_2D_ARRAY_EXTRACTOR);
			m_Quad = new SFQuad();
		}
		IV2DTextureArrayExtractQuadRenderer::~IV2DTextureArrayExtractQuadRenderer()
		{
			delete m_Quad;
		}

		void IV2DTextureArrayExtractQuadRenderer::Render()
		{
			m_Shader->Attach();
			m_Quad->Render();
		}
		void IV2DTextureArrayExtractQuadRenderer::RenderX()
		{
			m_Quad->Render();
		}

	}
}