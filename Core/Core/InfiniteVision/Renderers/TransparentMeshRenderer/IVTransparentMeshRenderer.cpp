#include "IVTransparentMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVTransparentMeshRenderer::~IVTransparentMeshRenderer()
		{

		}

		void IVTransparentMeshRenderer::Render(IVRenderStack::IVDrawData& _data)
		{
			for (auto iter = _data.begin(); iter != _data.end(); iter++)
			{
				std::pair<Shader*, std::vector<lwStaticMeshPkg*>>& draw_data = iter->second;
				draw_data.first->Attach();
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