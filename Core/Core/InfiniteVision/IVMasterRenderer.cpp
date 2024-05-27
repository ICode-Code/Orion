#include "IVMasterRenderer.h"
#include "../Scene/Scene.h"
#include "../ActiveEntity/ActiveEntity.h"

#include "LogUI.h" 

namespace OE1Core
{
	namespace Renderer
	{
		IVMasterRenderer::IVMasterRenderer(SDL_Window* _window, class OE1Core::Scene* _scene)
			: m_Scene{ _scene }
		{
			m_ModelPreviewRenderer = new IVModelPreviewRenderer(_window);
			m_MeshRenderer = new IVMeshRenderer();
			m_OutlineRenderer = new IVOutlineRenderer();
			m_ViewportBillboardRenderer = new IVViewportBillboardIconRenderer();
			m_MaterialPreviewRenderer = new IVMaterialPreviewRenderer();
			m_DebugShapeRenderer = new IVDebugShapeRenderer();
			m_SceneDebugShapeRenderer = new IVSceneDebugShapeRenderer();
			m_FullScreenQuadRenderer = new IVFullScreenQuadRenderer();
			m_DefferedLightPassRenderer = new IVDefferedLightPassRenderer();
		}
		IVMasterRenderer::~IVMasterRenderer()
		{
			delete m_ModelPreviewRenderer;
			delete m_MeshRenderer;
			delete m_OutlineRenderer;
			delete m_ViewportBillboardRenderer;
			delete m_MaterialPreviewRenderer;
			delete m_SceneDebugShapeRenderer;
			delete m_FullScreenQuadRenderer;
			delete m_DefferedLightPassRenderer;
		}
		void IVMasterRenderer::PushToRenderStack(StaticMesh* _mesh)
		{
			auto& mesh_package = _mesh->m_CoreMeshInstanceDescriptorSet;
			for (size_t i = 0; i < mesh_package.size(); i++)
			{
				if (mesh_package[i].Material->GetType() == MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentStaticMesh(&mesh_package[i], mesh_package[i].PackageID);
				else if (mesh_package[i].Material->GetType() == MaterialType::DEFAULT)
					m_Scene->m_RenderStack->RegisterFlatMaterialStaticMesh(&mesh_package[i], mesh_package[i].PackageID);
				else
					m_Scene->m_RenderStack->RegisterOpaqueStaticMesh(&mesh_package[i], mesh_package[i].PackageID);
			}
		}
		void IVMasterRenderer::PurgeFromRenderStack(StaticMesh* _mesh)
		{
			m_Scene->m_RenderStack->PurgeFromStack(_mesh->GetPackageID());
		}

		void IVMasterRenderer::PushToRenderStack(DynamicMesh* _mesh)
		{
			auto& mesh_package = _mesh->m_CoreMeshInstanceDescriptorSet;
			for (size_t i = 0; i < mesh_package.size(); i++)
			{
				if (mesh_package[i].Material->GetType() == MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentSkinnedMesh(&mesh_package[i], mesh_package[i].PackageID);
				else if (mesh_package[i].Material->GetType() == MaterialType::DEFAULT)
					m_Scene->m_RenderStack->RegisterFlatMaterialSkinnedMesh(&mesh_package[i], mesh_package[i].PackageID);
				else
					m_Scene->m_RenderStack->RegisterOpaqueSkinnedMesh(&mesh_package[i], mesh_package[i].PackageID);
			}
		}
		void IVMasterRenderer::PurgeFromRenderStack(DynamicMesh* _mesh)
		{
			m_Scene->m_RenderStack->PurgeFromStack(_mesh->GetPackageID());
		}

		void IVMasterRenderer::ReEvaluateRenderStackMaterial(MasterMaterial* _new_material)
		{
			if (!_new_material)
			{
				LOG_ERROR(LogLayer::Pipe("Invalid Master Material, Material Re-evaluation Process Fail!", OELog::CRITICAL));
				return;
			}
			
			// Collect the mesh by Material ID
			
			std::vector<CoreMeshInstanceRenderDescriptor*> re_evalutaion_buffer = m_Scene->m_RenderStack->QueryLWStaticMeshByMaterial(_new_material->GetOffset(), true);

			if (re_evalutaion_buffer.empty())
			{
				LOG_WARRNING(LogLayer::Pipe("Material Re-Evaluation Buffer is zero, no switch in static mesh occurred.", OELog::WARNING));
				return;
			}

			// Re-populate the buffer

			for (size_t i = 0; i < re_evalutaion_buffer.size(); i++)
			{
				if (re_evalutaion_buffer[i]->Material->GetType() == MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentStaticMesh(re_evalutaion_buffer[i], re_evalutaion_buffer[i]->PackageID);
				else if (re_evalutaion_buffer[i]->Material->GetType() == MaterialType::DEFAULT)
					m_Scene->m_RenderStack->RegisterFlatMaterialStaticMesh(re_evalutaion_buffer[i], re_evalutaion_buffer[i]->PackageID);
				else
					m_Scene->m_RenderStack->RegisterOpaqueStaticMesh(re_evalutaion_buffer[i], re_evalutaion_buffer[i]->PackageID);
			}
		}
		void IVMasterRenderer::MasterCameraPass(Component::CameraComponent* _master_camera)
		{

			_master_camera->MainFB()->Attach();

			int ActiveCameraIdx = _master_camera->GetBuffertOffset();

			m_MeshRenderer->Render(m_Scene->m_RenderStack, ActiveCameraIdx);


			m_OutlineRenderer->Render(m_Scene->GetActiveEntity(), ActiveCameraIdx);

			// Debug
			m_DebugShapeRenderer->Render(m_Scene->m_DebugMeshRegistry);
			//m_SceneDebugShapeRenderer->Render(m_Scene->m_TurboOctree->GetRootNode());


			m_ViewportBillboardRenderer->Render(m_Scene->m_SceneBillboardIcon, ActiveCameraIdx);

			m_GridRenderer.Render(*m_Scene->m_Grid, ActiveCameraIdx);

			_master_camera->MainFB()->Detach();

			DefferedLightPass(_master_camera);
		}
		void IVMasterRenderer::ClientCameraPass(Component::CameraComponent* _clinet_camera)
		{
			// IOF the camer is power off return
			if (_clinet_camera->GetPowerState() == CameraParameter::CAMERA_POWER_STATE::OFF)
				return;

			_clinet_camera->MainFB()->Attach();

			m_MeshRenderer->Render(m_Scene->m_RenderStack, _clinet_camera->GetBuffertOffset());

			_clinet_camera->MainFB()->Detach();
		}
		void IVMasterRenderer::FlushRenderCommand()
		{
			m_MeshRenderer->ResetDrawCount(m_Scene->m_RenderStack);
		}

		void IVMasterRenderer::RenderFullScreenQuadToDefaultFramebuffer(Component::CameraComponent* _camera, int _attachment_idx)
		{
			auto frame_buffer = _camera->MainFB();
			
			// BIND DEFAULT FRAMEBUFFER
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			
			glViewport(0, 0, frame_buffer->GetWidth(), frame_buffer->GetHeight());
			
			// Clear Default framebuffer
			frame_buffer->Clean(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			m_FullScreenQuadRenderer->Render(frame_buffer->GetAttachment(_attachment_idx));
		}

		void IVMasterRenderer::DefferedLightPass(Component::CameraComponent* _camera)
		{
			_camera->LightFB()->Attach();

			m_DefferedLightPassRenderer->Render(_camera);

			_camera->LightFB()->Detach();
		}
	}
}