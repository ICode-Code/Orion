#include "IVModelPreviewRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVModelPreviewRenderer::IVModelPreviewRenderer(SDL_Window* _window)
		{
			s_CameraPackage = new CameraPackage(_window, " ");
			s_LocalShader = ShaderManager::GetShader(ShaderID::MODEL_PREVIEW);
		}
		IVModelPreviewRenderer::~IVModelPreviewRenderer()
		{
			delete s_CameraPackage;    
		}

		void IVModelPreviewRenderer::Render(IVModel& _model_package)
		{
			GLint viewport[4];
			glGetIntegerv(GL_VIEWPORT, viewport);

			IVModelPreviewFramebuffer _frame(_model_package.Preview);
			_frame.SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			_frame.Attach();
			glViewport(0, 0, _frame.GetWidth(), _frame.GetHeight());
			s_LocalShader->Attach();

			s_CameraPackage->GetCamera()->SetResolution(glm::vec2(1280, 1024));
			s_CameraPackage->GetCamera()->m_Near = 0.01f;
			s_CameraPackage->GetController()->Focus(glm::vec3(0.0f, 0.0f, 0.0f), glm::length(_model_package.Extent * 1.5f));
			s_CameraPackage->GetController()->UpdateCameraView();

			s_CameraPackage->GetCamera()->Update(s_CameraPackage->GetController()->GetCurrentPosition());

			s_LocalShader->SetMat4("Model", glm::mat4(1.0f));
			s_LocalShader->SetMat4("View", s_CameraPackage->GetCamera()->m_View);
			s_LocalShader->SetMat4("Projection", s_CameraPackage->GetCamera()->m_Projection);


			for (size_t i = 0; i < _model_package.SubMeshs.size(); i++)
			{

				int id = _model_package.SubMeshs[i].MaterialID;
				s_LocalShader->Set1i("matIndex", id);
				s_LocalShader->Set1i("hasTexture", true);
				MasterMaterial* mat = MaterialManager::GetMaterial(id);
				if(!mat->HasColorMap())
					s_LocalShader->Set1i("hasTexture", false);

				mat->Attach();

				glBindVertexArray(_model_package.SubMeshs[i].VAO);
				glDrawElements(GL_TRIANGLES, _model_package.SubMeshs[i].IndicesCount, GL_UNSIGNED_INT, 0);
			}

			s_LocalShader->Detach();
			_frame.Detach();

			glViewport(viewport[0], viewport[1], viewport[2], viewport[3]);
		}
	}
}