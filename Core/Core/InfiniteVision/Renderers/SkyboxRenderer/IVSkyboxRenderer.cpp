#include "IVSkyboxRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVSkyboxRenderer::IVSkyboxRenderer()
		{
			m_Cube = new DS::Cube();
			m_Shader = ShaderManager::GetShader(ShaderID::SKYBOX);
		}
		IVSkyboxRenderer::~IVSkyboxRenderer()
		{
			delete m_Cube;
			m_Cube = nullptr;
		}

		void IVSkyboxRenderer::Render(GLuint _texture, int _camera_idx)
		{
			glDepthFunc(GL_LEQUAL);

			m_Shader->Attach();
			m_Shader->Set1i("ActiveCameraIndex", _camera_idx);
			m_Shader->SetMat4("Model", glm::mat4(1.0f));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);


			glBindVertexArray(m_Cube->m_VAO);
			glDrawArrays(GL_TRIANGLES, 0, 36);

			glBindVertexArray(0);
			m_Shader->Detach();

			glDepthFunc(GL_LESS);
		}
	}
}