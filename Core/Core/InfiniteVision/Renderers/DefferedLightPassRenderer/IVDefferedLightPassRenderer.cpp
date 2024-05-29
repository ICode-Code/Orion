#include "IVDefferedLightPassRenderer.h"
#include "../Core/Component/CameraComponent/CameraComponent.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVDefferedLightPassRenderer::IVDefferedLightPassRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::DEFFERED_LIGHT_PASS);
			m_Quad = new OE1Core::DS::Quad();

			m_Shader->Attach();
			m_Shader->Set1i("it_color",						0);
			m_Shader->Set1i("it_position",					1);
			m_Shader->Set1i("it_normal",					2);
			m_Shader->Set1i("it_emission",					3);
			m_Shader->Set1i("it_metal_roughness_ao_alpha",	4);
			m_Shader->Detach();
		}
		IVDefferedLightPassRenderer::~IVDefferedLightPassRenderer()
		{
			delete m_Quad;
		}

		void IVDefferedLightPassRenderer::Render(Component::CameraComponent* _camera)
		{
			m_Shader->Attach();
			m_Shader->Set1i("ActiveCameraIndex", _camera->GetBuffertOffset());

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_Color);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_Position);

			glActiveTexture(GL_TEXTURE2);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_Normal);

			glActiveTexture(GL_TEXTURE3);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_Emission);

			glActiveTexture(GL_TEXTURE4);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_MetalRougnessAOAlpha);




			glBindVertexArray(m_Quad->GetVAO());
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);

			m_Shader->Detach();
		}
	}
}