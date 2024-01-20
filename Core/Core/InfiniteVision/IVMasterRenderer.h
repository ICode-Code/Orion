#ifndef OE1_IV_MASTER_RENDERER_H_
#define OE1_IV_MASTER_RENDERER_H_

#include "DisplayCanavs/FrameSize.h"
#include "DisplayCanavs/IVForwardMainPassFramebuffer.h"

#include "Renderers/GridRenderer/IVGridRenderer.h"
#include "Renderers/ModelPreviewRenderer/IVModelPreviewRenderer.h"
#include "Renderers/MeshRenderer/IVMeshRenderer.h"
#include "Renderers/OutlineRenderer/IVOutlineRenderer.h"

// Render Stack
#include "RenderStack/RenderStack.h"
#include "../Mesh/StaticMesh/StaticMesh.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVMasterRenderer 
		{
		public:
			IVMasterRenderer(SDL_Window* _window, class OE1Core::Scene* _scene);
			~IVMasterRenderer();

			/// <summary>
			/// This function is called when ever there is a material update,
			/// Since the master renderer structure it's mesh based on the material for efficent rendering
			/// updating the material require the MasterRenderer update/restrusturing also
			/// for example all the transparent mesh rendered after the opaqe mesh, so if we
			/// made the material type transparent or vice versa at the middel of rendering process 
			/// the renderer need to re-evaluate all the mesh that uses this material and render them after the mesh that uses
			/// opaque material
			/// </summary>
			/// <param name="_prev_mat_type">What was the material type before it get updated, Until this moment the renderer know the original type, even though the material value is chnaged</param>
			/// <param name="_new_material">and Pointer to the material</param>
			void ReEvaluateRenderStackMaterial(MaterialType _prev_mat_type, MasterMaterial* _new_material);
			void PushToRenderStack(StaticMesh* _mesh);
			void PurgeFromRenderStack(StaticMesh* _mesh);
			void Update(int _width, int _height);
			void MasterPass();
			IVForwardMainPassFramebuffer& GetMainPassFramebuffer();
			inline IVGridRenderer& GetGridRenderer() { return m_GridRenderer; };
		protected: // Renderer
			IVGridRenderer m_GridRenderer;
			IVModelPreviewRenderer* m_ModelPreviewRenderer = nullptr;
			IVMeshRenderer* m_MeshRenderer = nullptr;
			IVOutlineRenderer* m_OutlineRenderer = nullptr;

		protected: // Framebuffer
			IVForwardMainPassFramebuffer m_MainPassFramebuffer;
			class OE1Core::Scene* m_Scene = nullptr;
		};
	}
}

#endif // !OE1_IV_MASTER_RENDERER_H_
