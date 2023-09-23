#include "IVMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVMeshRenderer::IVMeshRenderer()
		{
			m_OpaqueMeshRenderer = new IVOpaqueMeshRenderer();
		}
		IVMeshRenderer::~IVMeshRenderer()
		{
			delete m_OpaqueMeshRenderer;
		}

		void IVMeshRenderer::Render(IVRenderStack* _render_stack)
		{
			m_OpaqueMeshRenderer->Render(_render_stack->s_OpaqueMeshList);
		}
	}
}