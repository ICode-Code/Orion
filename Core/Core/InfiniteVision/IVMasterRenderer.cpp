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
		void IVMasterRenderer::PurgeFromRenderStack(StaticMesh* _mesh)
		{
			auto& mesh_package = _mesh->m_StaticMeshPkg;

			for (size_t i = 0; i < mesh_package.size(); i++)
			{

				if ((int)mesh_package[i].Material->GetType() & (int)MaterialType::ALPHA)
					m_Scene->m_RenderStack->RemoveTransparentMesh(mesh_package[i].Material->GetType());
				else
					m_Scene->m_RenderStack->RemoveOpaqueMesh(mesh_package[i].Material->GetType());

			}
		}
		void IVMasterRenderer::ReEvaluateRenderStackMaterial(MaterialType _prev_mat_type, MasterMaterial* _new_material)
		{
			// Let's get the mesh list which use this material type
			auto _Draw_list = m_Scene->m_RenderStack->GetDrawList(_prev_mat_type);
			if (!_Draw_list)
				return;
			std::unordered_map<uint32_t, StaticMesh*> _all_mesh_parent;
			
			for (size_t i = 0; i < _Draw_list->second.size(); i++)
			{
				if (_all_mesh_parent.find(_Draw_list->second[i]->PackageID) == _all_mesh_parent.end())
					_all_mesh_parent.insert(std::make_pair(_Draw_list->second[i]->PackageID, m_Scene->m_StaticMeshRegistry[_Draw_list->second[i]->PackageID]));
				
			}

			// Since we gonne re add theme, first we gonne remobve them all
			m_Scene->m_RenderStack->SearchAndDestroy(_prev_mat_type);

			// Now add them now doing this will perform the re-evaluation
			for (auto iter = _all_mesh_parent.begin(); iter != _all_mesh_parent.end(); iter++)
				PushToRenderStack(iter->second);

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

			
			m_OutlineRenderer->Render(m_Scene->GetActiveEntity());

			m_GridRenderer.Render(*m_Scene->m_Grid);

			m_MainPassFramebuffer.Detach();


			// Update Frame
			ViewportArgs::FINAL_FRAME = m_MainPassFramebuffer.GetAttachment(0);
		}
	}
}