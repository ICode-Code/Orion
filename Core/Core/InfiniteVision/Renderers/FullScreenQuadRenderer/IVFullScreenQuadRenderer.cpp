#include "IVFullScreenQuadRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVFullScreenQuadRenderer::IVFullScreenQuadRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::FULL_SCREEN_QUAD);
			m_Quad = new OE1Core::DS::Quad();
		}
		IVFullScreenQuadRenderer::~IVFullScreenQuadRenderer()
		{
			delete m_Quad;
		}

		void IVFullScreenQuadRenderer::Render(GLuint _texture)
		{
			m_Shader->Attach();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _texture);
			glBindVertexArray(m_Quad->m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			m_Shader->Detach();
		}

	}
}