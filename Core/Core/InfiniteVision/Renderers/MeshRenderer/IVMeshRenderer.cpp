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

		void IVMeshRenderer::Render(IVRenderStack* _render_stack, int _camera_idx)
		{
			m_FlatMaterialMeshRenderer->Render(_render_stack->s_FlatMaterialMeshList, _camera_idx);
			m_OpaqueMeshRenderer->Render(_render_stack->s_OpaqueMeshList, _camera_idx);
			m_TransparentMeshRenderer->Render(_render_stack->s_TransparentMeshList, _camera_idx);
		}
	}
}