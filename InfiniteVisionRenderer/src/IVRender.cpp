#include "IVRender.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVRender::IVRender(SceneInterface* _scene_interface)
			: m_SceneInterface{ _scene_interface }
		{

		}
		IVRender::~IVRender()
		{

		}

		unsigned int IVRender::RenderScene()
		{
			m_SceneInterface->UpdateScene();

			return 0;
		}
	}
}