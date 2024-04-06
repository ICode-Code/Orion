#include "IVSceneDebugShapeRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVSceneDebugShapeRenderer::IVSceneDebugShapeRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::SCENE_DEBUG_SHAPE);
		}
		IVSceneDebugShapeRenderer::~IVSceneDebugShapeRenderer()
		{

		}

		void IVSceneDebugShapeRenderer::Render(const DS::TurboOTNode& _root_node)
		{
			m_Shader->Attach();
			m_Shader->SetMat4("Model", glm::mat4(1.0f));

			RecursiveDraw(_root_node);
		}
		void IVSceneDebugShapeRenderer::Render(const DS::TurboOTNode& _root_node, int _camera_idx)
		{

		}

		void IVSceneDebugShapeRenderer::RecursiveDraw(const DS::TurboOTNode& _root_node)
		{

			if (_root_node.m_Data.size() > 0)
			{
				glBindVertexArray(_root_node.m_VisualizationVAO);

				glDrawArrays(GL_LINE_LOOP, 0, 24);

				glBindVertexArray(0);
			}
			
			if (!_root_node.m_Leaf)
			{
				for (size_t i = 0; i < CHILD_PER_OT_NODE; i++)
					RecursiveDraw(*_root_node.m_Child[i]);
			}
		}
	}
}