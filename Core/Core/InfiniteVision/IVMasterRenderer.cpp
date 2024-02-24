#include "IVMasterRenderer.h"
#include "../Scene/Scene.h"
#include "../ActiveEntity/ActiveEntity.h"

#include "LogUI.h" 

namespace OE1Core
{
	namespace Renderer
	{
		IVMasterRenderer::IVMasterRenderer(SDL_Window* _window, class OE1Core::Scene* _scene)
			: m_MainPassFramebuffer{ IVFrameSize::R_1k }, m_Scene{ _scene }
		{
			m_ModelPreviewRenderer = new IVModelPreviewRenderer(_window);
			m_MeshRenderer = new IVMeshRenderer();
			m_OutlineRenderer = new IVOutlineRenderer();
			m_ViewportBillboardRenderer = new IVViewportBillboardIconRenderer();
			m_MaterialPreviewRenderer = new IVMaterialPreviewRenderer();
		}
		IVMasterRenderer::~IVMasterRenderer()
		{
			delete m_ModelPreviewRenderer;
			delete m_MeshRenderer;
			delete m_OutlineRenderer;
			delete m_ViewportBillboardRenderer;
			delete m_MaterialPreviewRenderer;
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
		void IVMasterRenderer::Update(int _width, int _height)
		{
			m_MainPassFramebuffer.Update(_width, _height);
		}
		IVForwardMainPassFramebuffer& IVMasterRenderer::GetMainPassFramebuffer() { return m_MainPassFramebuffer; }
		void IVMasterRenderer::MasterPass(std::map<std::string, CameraParameters>& _cameras)
		{
			 
			MainViewportPass(m_Scene->m_MasterCamera, 0);

			auto cam_iteration_alpha = std::next(_cameras.begin()); // Ignore the main camera

			for (auto cam = cam_iteration_alpha; cam != _cameras.end(); cam++)
			{
				if (!cam->second.Camera->IsPowerOn())
					continue;

				CleanGamePass(cam->second.Camera, cam->second.Offset);
			}



			// Update Frame
			ViewportArgs::FINAL_FRAME = m_MainPassFramebuffer.GetAttachment(0);
		}

		void IVMasterRenderer::CleanGamePass(CameraPackage* _dynamic_camera, int _offset)
		{
			_dynamic_camera->AttachFramebuffer();

			int ActiveCameraIdx = _offset;

			m_MeshRenderer->Render(m_Scene->m_RenderStack, ActiveCameraIdx);


			_dynamic_camera->DetachFramebuffer();
		}
		void IVMasterRenderer::MainViewportPass(CameraPackage* _master_camera, int _offset)
		{
			_master_camera->AttachFramebuffer();

			int ActiveCameraIdx = _offset;

			m_MeshRenderer->Render(m_Scene->m_RenderStack, ActiveCameraIdx);


			m_OutlineRenderer->Render(m_Scene->GetActiveEntity(), ActiveCameraIdx);

			m_ViewportBillboardRenderer->Render(m_Scene->m_SceneBillboardIcon, ActiveCameraIdx);

			m_GridRenderer.Render(*m_Scene->m_Grid, ActiveCameraIdx);

			_master_camera->DetachFramebuffer();
		}
	}
}