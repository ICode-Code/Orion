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

		void IVGridRenderer::Render(const Grid& _grid, int _camera_idx)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glBlendEquation(GL_FUNC_ADD);

			m_Shader->Attach();
			m_Shader->Set1i("ActiveCameraIndex", _camera_idx);
			glBindVertexArray(_grid.m_VAO);
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, 1, 0);
			glBindVertexArray(0);

		}
	}
}