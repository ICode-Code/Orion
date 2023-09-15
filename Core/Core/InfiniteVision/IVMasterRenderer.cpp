#include "IVMasterRenderer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVMasterRenderer::IVMasterRenderer()
			: m_MainPassFramebuffer{ IVFrameSize::R_1k }
		{

		}
		IVMasterRenderer::~IVMasterRenderer()
		{

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