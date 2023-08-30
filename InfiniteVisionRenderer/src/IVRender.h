#ifndef OE1_INFINITE_VISION_RENDER_H_
#define OE1_INFINITE_VISION_RENDER_H_


#include "SceneInterface.h"

#include <functional>

namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) IVRender
		{
		public:
			IVRender(SceneInterface* _scene_interface);
			~IVRender();

			void Update(int _width, int _height);
			unsigned int RenderScene();

		protected:
			SceneInterface* m_SceneInterface = nullptr;
		};
	}
}

#endif // !OE1_INFINITE_VISION_RENDER_H_
