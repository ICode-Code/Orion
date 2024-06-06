#ifndef OE1_IV_FINAL_COLOR_BLEND_PASS_RENDERER_H_
#define OE1_IV_FINAL_COLOR_BLEND_PASS_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../Core/DS/Quad/Quad.h"


namespace OE1Core
{
	namespace Component
	{
		class CameraComponent;
	}
	namespace Renderer
	{
		class IVFinalColorBlendPassRenderer : public IVBaseRenderer
		{
		public:
			IVFinalColorBlendPassRenderer();
			~IVFinalColorBlendPassRenderer();

			void Render(class Component::CameraComponent* _camera);

		protected:

			OE1Core::DS::Quad* m_Quad = nullptr;
		};
	}
}



#endif // !OE1_IV_FINAL_COLOR_BLEND_PASS_RENDERER_H_
