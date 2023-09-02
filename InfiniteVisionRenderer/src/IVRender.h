#ifndef OE1_INFINITE_VISION_RENDER_H_
#define OE1_INFINITE_VISION_RENDER_H_


#include "Interface/CoreSystemInterface.h"
#include "Interface/SceneInterface.h"
#include "Interface.h"

// Framebuffer
#include "DisplayCanvas/Forward/IVFMainCanavs.h"

// Renderer
#include "GridRenderer/GridRenderer.h"

#include <functional>

namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) IVRender
		{
		public:
			IVRender(SceneInterface* _scene_interface, CoreSystemInterface* _core_system_interface);
			~IVRender();

			void Update(int _width, int _height);
			void RenderScene();

		protected:
			SceneInterface* m_SceneInterface = nullptr;
			CoreSystemInterface* m_CoreSystemInterface = nullptr;

		protected: // framebuffer
			IVFMainCanavs* m_IVMainCanavas = nullptr;

		protected: // Renderer
			GridRenderer* m_GridRenderer = nullptr;


		private: // Util
			void InitRenderer();
			void InitFramebuffer();
		};
	}
}

#endif // !OE1_INFINITE_VISION_RENDER_H_
