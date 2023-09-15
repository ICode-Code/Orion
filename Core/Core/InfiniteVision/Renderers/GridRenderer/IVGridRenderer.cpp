#include "IVGridRenderer.h" 


namespace OE1Core
{
	namespace Renderer
	{
		IVGridRenderer::IVGridRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::INIF_GRID);
		}
		IVGridRenderer::~IVGridRenderer()
		{

		}

		void IVGridRenderer::Render(const Grid& _grid)
		{
			m_Shader->Attach();
			glBindVertexArray(_grid.m_VAO);
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, 1, 0);
			glBindVertexArray(0);
		}
	}
}