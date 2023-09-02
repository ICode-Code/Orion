#include "IVRender.h"
#include "Shared/ViewportArgs.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRender::IVRender(SceneInterface* _scene_interface, CoreSystemInterface* _core_system_interface)
			: m_SceneInterface{ _scene_interface }, m_CoreSystemInterface{ _core_system_interface }
		{
			m_SceneInterface->GetScene()->SetRendererCallBack(
				[this](int _width, int _height)
				{ 
					this->Update(_width, _height); 
				}
			);

			InitFramebuffer();
			InitRenderer();

			
		}
		IVRender::~IVRender()
		{
			delete m_GridRenderer;

			delete m_IVMainCanavas;
		}
		void IVRender::InitRenderer()
		{
			m_GridRenderer = new GridRenderer(m_SceneInterface, m_CoreSystemInterface);
		}
		void IVRender::InitFramebuffer()
		{
			m_IVMainCanavas = new IVFMainCanavs(IVFrameSize::R_1k);
		}
		void IVRender::Update(int _width, int _height)
		{
			m_IVMainCanavas->Update(_width, _height);
		}
		unsigned int IVRender::RenderScene()
		{
			m_IVMainCanavas->Attach();

			m_SceneInterface->UpdateScene();

			m_GridRenderer->Render();

			m_IVMainCanavas->Detach();

			return ViewportArgs::FINAL_FRAME = m_IVMainCanavas->GetAttachment(0);
		}
	}
}