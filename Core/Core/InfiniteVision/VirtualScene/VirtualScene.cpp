#include "VirtualScene.h"



namespace OE1Core
{
	VirtualScene::VirtualScene(SDL_Window* _win_contex)
	{
		m_WindowContext = _win_contex;
		m_VirtualSceneCamera = new CameraPackage(m_WindowContext);
	}
	VirtualScene::~VirtualScene()
	{
		delete m_VirtualSceneCamera;
	}
}