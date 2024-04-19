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
			// Static Mesh Mesh
			m_FlatMaterialMeshRenderer->Render(_render_stack->m_STATIC_MESH_FLAT_MATERIAL_BUFFER, _camera_idx);
			m_OpaqueMeshRenderer->Render(_render_stack->m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER, _camera_idx);
			m_TransparentMeshRenderer->Render(_render_stack->m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _camera_idx);

			// Dynamic Mesh
			m_FlatMaterialMeshRenderer->Render(_render_stack->m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER, _camera_idx);
			m_OpaqueMeshRenderer->Render(_render_stack->m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER, _camera_idx);
			m_TransparentMeshRenderer->Render(_render_stack->m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _camera_idx);

		}
		void IVMeshRenderer::ResetDrawCount(IVRenderStack* _render_stack)
		{
			for (auto iter = _render_stack->m_STATIC_MESH_FLAT_MATERIAL_BUFFER.begin(); iter != _render_stack->m_STATIC_MESH_FLAT_MATERIAL_BUFFER.end(); iter++)
				ResteStaticMeshDrawCount(iter->second);

			for (auto iter = _render_stack->m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER.begin(); iter != _render_stack->m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER.end(); iter++)
				ResteStaticMeshDrawCount(iter->second);

			for (auto iter = _render_stack->m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER.begin(); iter != _render_stack->m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER.end(); iter++)
				ResteStaticMeshDrawCount(iter->second);
		}
		void IVMeshRenderer::ResteStaticMeshDrawCount(Core::IVCoreDrawStaticMeshPackage& _draw_pkg)
		{
			for (size_t i = 0; i < _draw_pkg.MESH_LIST.size(); i++)
				_draw_pkg.MESH_LIST[i]->DrawCount = 0;
		}
	}
}