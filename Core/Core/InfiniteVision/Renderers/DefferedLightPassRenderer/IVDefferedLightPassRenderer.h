#ifndef OE1_IV_DEFFERED_LIGHT_PASS_RENDERER_H_
#define OE1_IV_DEFFERED_LIGHT_PASS_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../Core/DS/Quad/Quad.h"


namespace OE1Core
{
	namespace Component {
		class CameraComponent;
	}
	namespace Renderer
	{
		class IVDefferedLightPassRenderer : public IVBaseRenderer
		{
		public:
			IVDefferedLightPassRenderer();
			~IVDefferedLightPassRenderer();

			void Render(class Component::CameraComponent* _camera);

		protected:
			OE1Core::DS::Quad* m_Quad = nullptr;
		};
	}
}



#endif // !OE1_IV_DEFFERED_LIGHT_PASS_RENDERER_H_
