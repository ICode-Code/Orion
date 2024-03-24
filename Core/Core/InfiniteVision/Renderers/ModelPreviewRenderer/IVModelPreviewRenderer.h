#ifndef OE1_IV_MODEL_PREVIEW_RENDERER_H_
#define OE1_IV_MODEL_PREVIEW_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../../../CameraPackage/CameraPackage.h"
#include "../../DisplayCanavs/IVModelPreviewFramebuffer.h"
#include "../../../MeshCluster/IVModel.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVModelPreviewRenderer : public IVBaseRenderer
		{
		public:
			IVModelPreviewRenderer(SDL_Window* _window);
			~IVModelPreviewRenderer();

			static void Render(IVModel& _model_package);

		protected:
			inline static CameraPackage* s_CameraPackage = nullptr;
			inline static Component::BaseCameraControllerComponent* s_CameraController = nullptr;
			inline static Shader* s_LocalShader = nullptr;
		};
	}
}

#endif // !OE1_IV_MODEL_PREVIEW_RENDERER_H_
