#include "IVModelPreviewRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVModelPreviewRenderer::IVModelPreviewRenderer(SDL_Window* _window)
		{
			s_CameraPackage = new CameraPackage(_window);
			s_LocalShader = ShaderManager::GetShader(ShaderID::MODEL_PREVIEW);
		}
		IVModelPreviewRenderer::~IVModelPreviewRenderer()
		{
			delete s_CameraPackage;
		}

		void IVModelPreviewRenderer::Render(ModelPkg& _model_package)
		{
			IVModelPreviewFramebuffer _frame(_model_package.SnapShot);
			_frame.SetClearColor({ 0.0f, 0.0f, 0.0f, 0.0f });
			_frame.Attach();
			s_LocalShader->Attach();

			s_CameraPackage->GetCamera()->SetResolution(glm::vec2(IVFrameSize::R_1k[0], IVFrameSize::R_1k[1]));
			
			s_CameraPackage->GetController()->Focus(glm::vec3(1.0f), glm::length(_model_package.Extents));
			s_CameraPackage->GetController()->UpdateCameraView();

			s_CameraPackage->GetCamera()->Update(s_CameraPackage->GetController()->GetCurrentPosition());

			s_LocalShader->SetMat4("Model", glm::translate(glm::mat4(1.0f), glm::vec3(1.0f)));
			s_LocalShader->SetMat4("View", s_CameraPackage->GetCamera()->m_View);
			s_LocalShader->SetMat4("Projection", s_CameraPackage->GetCamera()->m_Projection);

			

			for (size_t i = 0; i < _model_package.MeshList.size(); i++)
			{
				glBindVertexArray(_model_package.MeshList[i].VAO);
				glDrawElements(GL_TRIANGLES, _model_package.MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);
			}

			s_LocalShader->Detach();
			_frame.Detach();
		}
	}
}