#include "IVFinalColorBlendPassRenderer.h"
#include "../Core/Component/CameraComponent/CameraComponent.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVFinalColorBlendPassRenderer::IVFinalColorBlendPassRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::FINAL_COLOR_BLEND);
			m_Quad = new OE1Core::DS::Quad();

			m_Shader->Attach();

			m_Shader->Set1i("it_color", 0);
			m_Shader->Set1i("it_bloom", 1);

			m_Shader->Detach();
		}
		IVFinalColorBlendPassRenderer::~IVFinalColorBlendPassRenderer()
		{
			delete m_Quad;
		}

		void IVFinalColorBlendPassRenderer::Render(Component::CameraComponent* _camera)
		{
			m_Shader->Attach();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _camera->LightFB()->GetAttachment(0));

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _camera->PostProcessBloomFM()->GetAttachment(0));

			glBindVertexArray(m_Quad->GetVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			glBindVertexArray(0);
			m_Shader->Detach();
		}
	}
}