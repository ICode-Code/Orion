#include "IVMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVMeshRenderer::IVMeshRenderer()
		{
			m_OpaqueMeshRenderer = new IVOpaqueMeshRenderer();
			m_FlatMaterialMeshRenderer = new IVFlatMaterialMeshRenderer();
			m_TransparentMeshRenderer = new IVTransparentMeshRenderer();
		}
		IVMeshRenderer::~IVMeshRenderer()
		{
			delete m_OpaqueMeshRenderer;
			delete m_FlatMaterialMeshRenderer;
			delete m_TransparentMeshRenderer;
		}

		void IVMeshRenderer::Render(IVRenderStack* _render_stack)
		{
			m_OpaqueMeshRenderer->Render(_render_stack->s_OpaqueMeshList);
			m_FlatMaterialMeshRenderer->Render(_render_stack->s_FlatMaterialMeshList);
			m_TransparentMeshRenderer->Render(_render_stack->s_TransparentMeshList);
		}
	}
}