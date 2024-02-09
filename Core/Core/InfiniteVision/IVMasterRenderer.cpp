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
		void IVMasterRenderer::PushToRenderStack(class StaticMesh* _mesh)
		{
			auto& mesh_package = _mesh->m_StaticMeshPkg;
			for (size_t i = 0; i < mesh_package.size(); i++)
			{
				if (mesh_package[i].Material->GetType() == MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentMesh(&mesh_package[i], _mesh->GetPackageID());
				else if (mesh_package[i].Material->GetType() == MaterialType::DEFAULT)
					m_Scene->m_RenderStack->RegisterFlatMaterialMesh(&mesh_package[i], _mesh->GetPackageID());
				else
					m_Scene->m_RenderStack->RegisterOpaqueMesh(&mesh_package[i], _mesh->GetPackageID());
			}
		}
		void IVMasterRenderer::PurgeFromRenderStack(StaticMesh* _mesh)
		{
			m_Scene->m_RenderStack->PurgeFromStack(_mesh->GetPackageID());
		}
		void IVMasterRenderer::ReEvaluateRenderStackMaterial(MaterialType _prev_mat_type, MasterMaterial* _new_material, uint32_t _mesh_id)
		{
			if (_mesh_id < 0)
			{
				LOG_ERROR("Invalid StaticMesh ID master material re-evaluation process fail!");
				return;
			}
			
			//StaticMesh* _mesh = m_Scene->m_StaticMeshRegistry[_mesh_id];
			
			std::vector<lwStaticMeshPkg*> re_evalutaion_buffer = m_Scene->m_RenderStack->QueryLWStaticMesh(_mesh_id, true);

			if (re_evalutaion_buffer.empty())
			{
				LOG_WARRNING(LogLayer::Pipe("Material Re-Evaluation Buffer is zero, no switch in static mesh occurred.", OELog::WARNING));
				return;
			}

			// Re-populate the buffer

			for (size_t i = 0; i < re_evalutaion_buffer.size(); i++)
			{
				if (re_evalutaion_buffer[i]->Material->GetType() == MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentMesh(re_evalutaion_buffer[i], _mesh_id);
				else if (re_evalutaion_buffer[i]->Material->GetType() == MaterialType::DEFAULT)
					m_Scene->m_RenderStack->RegisterFlatMaterialMesh(re_evalutaion_buffer[i], _mesh_id);
				else
					m_Scene->m_RenderStack->RegisterOpaqueMesh(re_evalutaion_buffer[i], _mesh_id);
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

			auto cam_iteration_alpha = std::next(_cameras.begin());
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


			//m_OutlineRenderer->Render(m_Scene->GetActiveEntity(), ActiveCameraIdx);

			//m_ViewportBillboardRenderer->Render(m_Scene->m_SceneBillboardIcon, ActiveCameraIdx);

			m_GridRenderer.Render(*m_Scene->m_Grid, ActiveCameraIdx);

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