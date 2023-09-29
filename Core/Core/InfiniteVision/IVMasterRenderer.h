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
