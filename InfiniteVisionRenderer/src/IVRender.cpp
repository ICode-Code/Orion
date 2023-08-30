#include "IVRender.h"
#include "Shared/ViewportArgs.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVRender::IVRender(SceneInterface* _scene_interface)
			: m_SceneInterface{ _scene_interface }
		{
			m_SceneInterface->GetScene()->SetRendererCallBack(
				[this](int _width, int _height)
				{ 
					this->Update(_width, _height); 
				}
			);
		}
		IVRender::~IVRender()
		{

		}
		void IVRender::Update(int _width, int _height)
		{
			printf("Updated {%i}, {%i}\n", _width, _height);
		}
		unsigned int IVRender::RenderScene()
		{
			m_SceneInterface->UpdateScene();
			ViewportArgs::FINAL_FRAME = 0;
			return 0;
		}
	}
}