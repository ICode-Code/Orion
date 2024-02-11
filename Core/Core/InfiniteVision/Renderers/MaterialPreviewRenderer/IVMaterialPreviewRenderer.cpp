#include "IVMaterialPreviewRenderer.h"
#include "../../../Scene/Scene.h"
#include <glm/glm.hpp>

namespace OE1Core
{
	namespace Renderer
	{
		IVMaterialPreviewRenderer::IVMaterialPreviewRenderer()
		{
			m_VirtualRenderMesh = AssetManager::GetGeometryI(DynamicAssetType::SPHERE);
			s_LocalShader = ShaderManager::GetShader(ShaderID::MATERIAL_PREVIEW);
		}
		IVMaterialPreviewRenderer::~IVMaterialPreviewRenderer()
		{

		}

		void IVMaterialPreviewRenderer::Refresh(MasterMaterial* _material, Scene* _scene)
		{
			glDeleteTextures(1, &_material->m_Preview);
			Render(_material, _scene);
		}
		void IVMaterialPreviewRenderer::Render(MasterMaterial* _material, Scene* _scene)
		{

			// Create, setup, and position the camera
			std::string PREVIEW_CAMERA_TAG = "MaterialPreivewCam";
			CameraPackage* PREVIEW_CAMERA = _scene->GetCameraManager()->RegisterCamera(PREVIEW_CAMERA_TAG);
			int PREVIEW_CAMERA_TAG_IDX = _scene->GetCameraManager()->GetCameraIndex(PREVIEW_CAMERA_TAG);
			
			IVVirtualMaterialSceneFramebuffer m_VirtualMaterialSceneFramebuffer(_material->m_Preview);// = new Renderer::IVVirtualMaterialSceneFramebuffer(_material->GetPreviewRef());
			m_VirtualMaterialSceneFramebuffer.SetClearColor({0.1f, 0.1f, 0.1f, 1.0f});
			m_VirtualMaterialSceneFramebuffer.Attach();

			
			PREVIEW_CAMERA->GetCamera()->m_Near = 0.01f;
			PREVIEW_CAMERA->GetController()->Focus(glm::vec3(0.0f, 0.0f, 0.0f), 2.0f);
			PREVIEW_CAMERA->GetController()->UpdateCameraView();
			PREVIEW_CAMERA->GetCamera()->Update(glm::vec3(3.0f, 0.0f, 0.0f));
			PREVIEW_CAMERA->Update(0.1f);

			Memory::UniformBlockManager::UseBuffer(
				Memory::UniformBufferID::SCENE_TRANSFORM)->Update(
					Memory::s_SceneTransformBufferSize,
					PREVIEW_CAMERA_TAG_IDX * Memory::s_SceneTransformBufferSize,
					&PREVIEW_CAMERA->GetSceneTransform());


			s_LocalShader->Attach();
			glm::mat4 Model = glm::mat4(1.0f);
			Model = glm::rotate(Model, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
			Model = glm::rotate(Model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			s_LocalShader->SetMat4("Model", Model);
			s_LocalShader->Set1i("ActiveCameraIndex", PREVIEW_CAMERA_TAG_IDX);

			s_LocalShader->Set1i("matIndex", _material->GetOffset());
			s_LocalShader->Set1i("hasTexture", true);
			if (!_material->HasColorMap())
				s_LocalShader->Set1i("hasTexture", false);

			_material->Attach();

			for (size_t i = 0; i < m_VirtualRenderMesh->MeshList.size(); i++)
			{
				glBindVertexArray(m_VirtualRenderMesh->MeshList[i].VAO);
				glDrawElements(GL_TRIANGLE_STRIP, m_VirtualRenderMesh->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);
			}

			s_LocalShader->Detach();
			m_VirtualMaterialSceneFramebuffer.Detach();
			_scene->GetCameraManager()->PurgeCamera(PREVIEW_CAMERA_TAG);
		}
	}
}