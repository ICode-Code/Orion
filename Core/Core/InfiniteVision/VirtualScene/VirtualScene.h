#ifndef OE1_VIRTUAL_SCENE_H_
#define OE1_VIRTUAL_SCENE_H_

#include "../../CameraPackage/CameraPackage.h"

namespace OE1Core
{
	class VirtualScene
	{
	public:
		VirtualScene(SDL_Window* _win_context);
		virtual ~VirtualScene();
	protected:
		inline static CameraPackage* m_VirtualSceneCamera = nullptr;
		inline static SDL_Window* m_WindowContext = nullptr;
	};
}

#endif // !OE1_VIRTUAL_SCENE_H_
