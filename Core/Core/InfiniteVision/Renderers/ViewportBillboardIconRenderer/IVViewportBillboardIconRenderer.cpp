#include "IVViewportBillboardIconRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVViewportBillboardIconRenderer::IVViewportBillboardIconRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::VIEWPORT_BILLBOARD_ICON_TEXTURE_PASS);
		}
		IVViewportBillboardIconRenderer::~IVViewportBillboardIconRenderer()
		{

		}

		void IVViewportBillboardIconRenderer::Render(std::unordered_map<ViewportIconBillboardType, ViewportBillboardIcon*>& _sprite_list)
		{
			m_Shader->Attach();

			for (auto iter = _sprite_list.begin(); iter != _sprite_list.end(); iter++)
			{
				if (iter->second->m_ActiveInstanceCount <= 0)
					continue;

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, iter->second->m_Texture->GetTexture());

				glBindVertexArray(iter->second->m_BaseQuad->m_VAO);

				glDrawElementsInstanced(GL_TRIANGLES, iter->second->m_BaseQuad->m_IndicesCount, GL_UNSIGNED_INT, 0, iter->second->m_ActiveInstanceCount);
			}
		 
			m_Shader->Detach();
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindVertexArray(0);
		}
	}
}