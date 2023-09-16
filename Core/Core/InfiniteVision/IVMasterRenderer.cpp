#include "IVMasterRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVMasterRenderer::IVMasterRenderer(SDL_Window* _window)
			: m_MainPassFramebuffer{ IVFrameSize::R_1k }
		{
			m_ModelPreviewRenderer = new IVModelPreviewRenderer(_window);
		}
		IVMasterRenderer::~IVMasterRenderer()
		{
			delete m_ModelPreviewRenderer;
		}

		void IVMasterRenderer::Update(int _width, int _height)
		{
			m_MainPassFramebuffer.Update(_width, _height);
		}

		void IVMasterRenderer::MasterPass(Scene& _scene)
		{
			m_MainPassFramebuffer.Attach();



			m_GridRenderer.Render(*_scene.m_Grid); 

			m_MainPassFramebuffer.Detach();


			// Update Frame
			ViewportArgs::FINAL_FRAME = m_MainPassFramebuffer.GetAttachment(0);
		}
	}
}