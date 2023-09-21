#include "IVMasterRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVMasterRenderer::IVMasterRenderer(SDL_Window* _window)
			: m_MainPassFramebuffer{ IVFrameSize::R_1k }
		{
			m_ModelPreviewRenderer = new IVModelPreviewRenderer(_window);
			m_SceneRenderer = new IVSceneRenderer();
		}
		IVMasterRenderer::~IVMasterRenderer()
		{
			delete m_ModelPreviewRenderer;
			delete m_SceneRenderer;
		}
		void IVMasterRenderer::PushToRenderStack(class StaticMesh* _mesh, class Scene* _scene)
		{
			auto& mesh_package = _mesh->m_StaticMeshPkg;
			for (size_t i = 0; i < mesh_package.size(); i++)
			{

				if ((int)mesh_package[i].Material->GetType() & (int)MaterialType::ALPHA)
					_scene->m_RenderStack->RegisterTransparentMesh(&mesh_package[i], mesh_package[i].Material->GetType());
				else 
					_scene->m_RenderStack->RegisterOpaqueMesh(&mesh_package[i], mesh_package[i].Material->GetType());

			}
		}
		void IVMasterRenderer::Update(int _width, int _height)
		{
			m_MainPassFramebuffer.Update(_width, _height);
		}

		void IVMasterRenderer::MasterPass(Scene* _scene)
		{
			m_MainPassFramebuffer.Attach();


			m_SceneRenderer->Render(_scene->m_RenderStack);


			m_GridRenderer.Render(*_scene->m_Grid); 

			m_MainPassFramebuffer.Detach();


			// Update Frame
			ViewportArgs::FINAL_FRAME = m_MainPassFramebuffer.GetAttachment(0);
		}
	}
}