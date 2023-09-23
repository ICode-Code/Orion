#include "IVMasterRenderer.h"
#include "../Scene/Scene.h"
#include "../ActiveEntity/ActiveEntity.h"

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
		}
		IVMasterRenderer::~IVMasterRenderer()
		{
			delete m_ModelPreviewRenderer;
			delete m_MeshRenderer;
			delete m_OutlineRenderer;
		}
		void IVMasterRenderer::PushToRenderStack(class StaticMesh* _mesh)
		{
			auto& mesh_package = _mesh->m_StaticMeshPkg;
			for (size_t i = 0; i < mesh_package.size(); i++)
			{

				if ((int)mesh_package[i].Material->GetType() & (int)MaterialType::ALPHA)
					m_Scene->m_RenderStack->RegisterTransparentMesh(&mesh_package[i], mesh_package[i].Material->GetType());
				else 
					m_Scene->m_RenderStack->RegisterOpaqueMesh(&mesh_package[i], mesh_package[i].Material->GetType());

			}
		}
		void IVMasterRenderer::Update(int _width, int _height)
		{
			m_MainPassFramebuffer.Update(_width, _height);
		}
		IVForwardMainPassFramebuffer& IVMasterRenderer::GetMainPassFramebuffer() { return m_MainPassFramebuffer; }
		void IVMasterRenderer::MasterPass()
		{

			m_MainPassFramebuffer.Attach();

			m_MeshRenderer->Render(m_Scene->m_RenderStack);

			
			m_OutlineRenderer->Render(*m_Scene->GetActiveEntity());

			m_GridRenderer.Render(*m_Scene->m_Grid);

			m_MainPassFramebuffer.Detach();


			// Update Frame
			ViewportArgs::FINAL_FRAME = m_MainPassFramebuffer.GetAttachment(0);
		}
	}
}