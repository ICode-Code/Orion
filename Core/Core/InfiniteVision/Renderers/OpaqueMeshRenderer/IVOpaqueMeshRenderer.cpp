#include "IVOpaqueMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVOpaqueMeshRenderer::~IVOpaqueMeshRenderer()
		{

		}

		void IVOpaqueMeshRenderer::Render(std::vector<lwStaticMeshPkg*>& _list)
		{
			//m_Shader->Attach();

			for (size_t i = 0; i < _list.size(); i++)
			{
				if (!_list[i]->DrawCount)
					continue;
				_list[i]->Material->GetShader()->Attach();
				_list[i]->Material->Attach();

				glBindVertexArray(_list[i]->VAO);
				glDrawElementsInstanced(GL_TRIANGLES, _list[i]->IndiceCount, GL_UNSIGNED_INT, 0, _list[i]->DrawCount);
			}
		}
	}
}