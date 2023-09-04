#include "GridRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		GridRenderer::GridRenderer(SceneInterface* _scene_interface, CoreSystemInterface* _coreSystem_interface)
			: BaseRenderer(_scene_interface, _coreSystem_interface)
		{
			m_Shader = m_CoreSystemInterface->GetShader(ShaderID::INIF_GRID);
			m_Grid = _scene_interface->GetSceneGrid();
		}
		GridRenderer::~GridRenderer()
		{

		}

		void GridRenderer::Render()
		{
			m_Shader->Attach();
			glBindVertexArray(m_Grid->m_VAO);
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, 1, 0);
			glBindVertexArray(0);
		}
	}
}