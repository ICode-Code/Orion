#ifndef OE1_IV_MODEL_PREVIEW_RENDERER_H_
#define OE1_IV_MODEL_PREVIEW_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../../../CameraPackage/CameraPackage.h"
#include "../../DisplayCanavs/IVModelPreviewFramebuffer.h"
#include "../../../MeshCluster/ModelPkg.h"
#

namespace OE1Core
{
	namespace Renderer
	{
		class IVModelPreviewRenderer : public IVBaseRenderer
		{
		public:
			IVModelPreviewRenderer(SDL_Window* _window);
			~IVModelPreviewRenderer();

			static void Render(ModelPkg& _model_package);

		protected:
			inline static CameraPackage* s_CameraPackage = nullptr;
			inline static Shader* s_LocalShader = nullptr;
		};
	}
}

#endif // !OE1_IV_MODEL_PREVIEW_RENDERER_H_
