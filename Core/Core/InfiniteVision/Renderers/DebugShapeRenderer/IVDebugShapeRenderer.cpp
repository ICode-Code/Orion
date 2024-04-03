#include "IVDebugShapeRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVDebugShapeRenderer::IVDebugShapeRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::LOCAL_DEBUG_SHAPE);
		}
		IVDebugShapeRenderer::~IVDebugShapeRenderer()
		{

		}

		void IVDebugShapeRenderer::Render(std::unordered_map<uint32_t, DebugMesh*>& _shapes)
		{
			m_Shader->Attach(); 

			for (auto iter = _shapes.begin(); iter != _shapes.end(); iter++)
			{
				auto core_mesh = iter->second->GetCoreMeshInstanceDescriptorSet();

				for (size_t i = 0; i < core_mesh.size(); i++)
				{
					glBindVertexArray(core_mesh[i].VAO);

					glDrawArraysInstanced(GL_LINE_LOOP, 0, core_mesh[i].VertexCount, core_mesh[i].DrawCount);

					glBindVertexArray(0);
				}
				
			}
		}
		void IVDebugShapeRenderer::Render(std::unordered_map<uint32_t, DebugMesh*>& _shapes, int _camera_idx)
		{

		}
	}
}