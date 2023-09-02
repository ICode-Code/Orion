#include "GridRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		GridRenderer::GridRenderer(SceneInterface* _scene_interface, CoreSystemInterface* _coreSystem_interface)
			: BaseRenderer(_scene_interface, _coreSystem_interface)
		{
			m_Shader = m_CoreSystemInterface->GetShader(ShaderID::INIF_GRID);
			glGenVertexArrays(1, &s_VAO);
			Update();
		}
		GridRenderer::~GridRenderer()
		{
			glDeleteVertexArrays(1, &s_VAO);
		}
		void GridRenderer::Update()
		{
			auto* buffer = Memory::UniformBlockManager::GetBuffer(Memory::UniformBufferID::INFIN_GRID);
			if (!buffer)
				return;

			Memory::InfiniteGrid grid;
			grid.Scale = s_Scale;
			grid.ColorBold = glm::vec4(s_ColorBold[0], s_ColorBold[1], s_ColorBold[2], s_ColorBold[3]);
			grid.ColorLight = glm::vec4(s_ColorLight[0], s_ColorLight[1], s_ColorLight[2], s_ColorLight[3]);

			buffer->Update(Memory::s_InfiniteGridBufferSize, 0, &grid);
		}

		void GridRenderer::Render()
		{
			m_Shader->Attach();
			glBindVertexArray(s_VAO);
			glDrawArraysInstancedBaseInstance(GL_TRIANGLES, 0, 6, 1, 0);
			glBindVertexArray(0);
		}
	}
}