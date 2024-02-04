#include "IVOpaqueMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVOpaqueMeshRenderer::~IVOpaqueMeshRenderer()
		{

		}

		void IVOpaqueMeshRenderer::Render(IVRenderStack::IVDrawData& _list, int _camera_idx)
		{
			for (auto iter = _list.begin(); iter != _list.end(); iter++)
			{
				std::pair<Shader*, std::vector<lwStaticMeshPkg*>>& draw_data = iter->second;
				draw_data.first->Attach();
				draw_data.first->Set1i("ActiveCameraIndex", _camera_idx);
				for (size_t i = 0; i < draw_data.second.size(); i++)
				{
					if (!draw_data.second[i]->DrawCount)
						continue;

					draw_data.second[i]->Material->Attach();
					glBindVertexArray(draw_data.second[i]->VAO);
					glDrawElementsInstanced(GL_TRIANGLES, draw_data.second[i]->IndiceCount, GL_UNSIGNED_INT, 0, draw_data.second[i]->DrawCount);

				}
			}
		}
	}
}