#ifndef OE1_IV_MASTER_RENDERER_H_
#define OE1_IV_MASTER_RENDERER_H_

#include "DisplayCanavs/FrameSize.h"
#include "DisplayCanavs/IVForwardMainPassFramebuffer.h"

#include "Renderers/GridRenderer/IVGridRenderer.h"
#include "Renderers/ModelPreviewRenderer/IVModelPreviewRenderer.h"

#include "../Scene/Scene.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVMasterRenderer
		{
		public:
			IVMasterRenderer(SDL_Window* _window);
			~IVMasterRenderer();

			void Update(int _width, int _height);
			void MasterPass(Scene& _scene);

			inline IVGridRenderer& GetGridRenderer() { return m_GridRenderer; };

		protected: // Renderer
			IVGridRenderer m_GridRenderer;
			IVModelPreviewRenderer* m_ModelPreviewRenderer = nullptr;

		protected: // Framebuffer
			IVForwardMainPassFramebuffer m_MainPassFramebuffer;
		};
	}
}

#endif // !OE1_IV_MASTER_RENDERER_H_
