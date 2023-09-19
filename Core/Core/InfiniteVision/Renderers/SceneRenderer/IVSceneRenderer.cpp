#include "IVSceneRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVSceneRenderer::IVSceneRenderer()
		{
			m_OpaqueMeshRenderer = new IVOpaqueMeshRenderer();
		}
		IVSceneRenderer::~IVSceneRenderer()
		{
			delete m_OpaqueMeshRenderer;
		}

		void IVSceneRenderer::Render(IVRenderStack* _render_stack)
		{
			m_OpaqueMeshRenderer->Render(_render_stack->s_OpaqueMeshList);
		}
	}
}