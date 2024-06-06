#include "IVHDRPreviewRenderer.h"
#include "../../../Scene/Scene.h"
#include <glm/glm.hpp>


namespace OE1Core
{
	namespace Renderer
	{
		IVHDRPreviewRenderer::IVHDRPreviewRenderer()
		{
			m_VirtualRenderMesh = AssetManager::GetGeometryI(DynamicAssetType::SPHERE);
			s_LocalShader = ShaderManager::GetShader(ShaderID::HDRI_PREVIEW);
		}
		IVHDRPreviewRenderer::~IVHDRPreviewRenderer()
		{

		}

		void IVHDRPreviewRenderer::Render(GLuint _src_hdri_texture, GLuint& _dest_preview_texture, Scene* _scene)
		{
			// Create, setup, and position the camera
			std::string PREVIEW_CAMERA_TAG = "HDRdomPreivewCam";
			uint64_t uid = 707070;

			// Create Camera
			Component::CameraComponent* PREVIEW_CAMERA = new Component::CameraComponent();
			_scene->GetCameraManager()->RegisterCamera(uid, PREVIEW_CAMERA);

			// Create Camera Controller
			Component::FreeLookCameraControllerComponent* Controller = new Component::FreeLookCameraControllerComponent(_scene->GetCameraManager()->GetContextWindow());
			Controller->SetCameraComponent(PREVIEW_CAMERA);

			// Setup Camera
			PREVIEW_CAMERA->m_Near = 0.01f;
			Controller->Focus(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f);
			Controller->UpdateInput(0.1f);
			PREVIEW_CAMERA->UpdateBuffer(0.1f);

			// Setup Framebuffer
			IVVirtualMaterialSceneFramebuffer* m_VirtualMaterialSceneFramebuffer = new Renderer::IVVirtualMaterialSceneFramebuffer(_dest_preview_texture);
			m_VirtualMaterialSceneFramebuffer->SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			m_VirtualMaterialSceneFramebuffer->Attach();

			s_LocalShader->Attach();
			glm::mat4 Model = glm::mat4(1.0f);
			//Model = glm::rotate(Model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			Model = glm::rotate(Model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			s_LocalShader->SetMat4("Model", Model);
			s_LocalShader->Set1i("ActiveCameraIndex", PREVIEW_CAMERA->GetBuffertOffset());


			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _src_hdri_texture);
			for (size_t i = 0; i < m_VirtualRenderMesh->SubMeshs.size(); i++)
			{
				glBindVertexArray(m_VirtualRenderMesh->SubMeshs[i].VAO);
				glDrawElements(GL_TRIANGLE_STRIP, m_VirtualRenderMesh->SubMeshs[i].IndicesCount, GL_UNSIGNED_INT, 0);
			}

			s_LocalShader->Detach();
			m_VirtualMaterialSceneFramebuffer->Detach();
			delete m_VirtualMaterialSceneFramebuffer;
			_scene->GetCameraManager()->PurgeCamera(uid);
			delete Controller;
			delete PREVIEW_CAMERA;



		}
	}
}