#include "IVModelPreviewRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVModelPreviewRenderer::IVModelPreviewRenderer(SDL_Window* _window)
		{
			s_Camera = new Component::CameraComponent();
			s_LocalShader = ShaderManager::GetShader(ShaderID::MODEL_PREVIEW);
			s_CameraController = new Component::FreeLookCameraControllerComponent(_window);

			s_CameraController->SetCameraComponent(s_Camera);
		}
		IVModelPreviewRenderer::~IVModelPreviewRenderer()
		{
			delete s_Camera;
			delete s_CameraController;
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

			float _length = glm::length(_model_package.Bound.Max);
			s_Camera->m_FieldOfView = 75;
			s_Camera->m_Far = 100000.0f;
			s_Camera->UpdateRenderFrameSize(1280, 1024);
			s_Camera->m_Near = 0.01f;
			s_CameraController->Focus(glm::vec3(0.0f, _length / 2.0f, 0.0f), _length);
			s_CameraController->UpdateCameraView();


			glm::vec3 _pos = glm::vec3(s_CameraController->GetFinalPosition().x, s_CameraController->GetFinalPosition().y, s_CameraController->GetFinalPosition().z);
			s_Camera->Update(_pos);

			s_LocalShader->SetMat4("Model", glm::mat4(1.0f));
			s_LocalShader->SetMat4("View", s_Camera->m_View);
			s_LocalShader->SetMat4("Projection", s_Camera->m_Projection);


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