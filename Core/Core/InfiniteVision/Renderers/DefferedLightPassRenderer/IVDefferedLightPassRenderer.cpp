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
			m_Shader->Set1i("it_Rdepth", 5);

			m_Shader->Set1i("it_irradiance_map",				6);
			m_Shader->Set1i("it_pre_filtered_enviroment_map",	7);
			m_Shader->Set1i("it_lookup_texture",				8);
			m_Shader->Detach();
		}
		IVDefferedLightPassRenderer::~IVDefferedLightPassRenderer()
		{
			delete m_Quad;
		}

		void IVDefferedLightPassRenderer::Render(Component::CameraComponent* _camera, IVLightRoom* _light_room)
		{
			m_Shader->Attach();
			m_Shader->Set1i("ActiveCameraIndex", _camera->GetBuffertOffset());
			m_Shader->Set1f("near", _camera->m_Near);
			m_Shader->Set1f("far", _camera->m_Far);

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

			glActiveTexture(GL_TEXTURE5);
			glBindTexture(GL_TEXTURE_2D, _camera->MainFB()->m_Rdepth);

			glActiveTexture(GL_TEXTURE6);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _light_room->IrradianceMap);

			glActiveTexture(GL_TEXTURE7);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _light_room->PreFilteredEnviromentMap);

			glActiveTexture(GL_TEXTURE8);
			glBindTexture(GL_TEXTURE_2D, _light_room->LUT);


			glBindVertexArray(m_Quad->GetVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);

			m_Shader->Detach();
		}
	}
}