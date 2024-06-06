#ifndef OE1_IV_SKYBOX_PREVIEW_RENDERER_H_
#define OE1_IV_SKYBOX_PREVIEW_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../../DisplayCanavs/IVVirtualMaterialSceneFramebuffer.h"

namespace OE1Core
{
	class Scene;
	namespace Renderer
	{
		class IVSkyboxPreviewRenderer : public IVBaseRenderer
		{
		public:
			IVSkyboxPreviewRenderer();
			~IVSkyboxPreviewRenderer();

			static void Render(GLuint _src_sky_dom_texture, GLuint& _dest_preview_texture, Scene* _scene);

		private:
			inline static struct IVModel* m_VirtualRenderMesh = nullptr;
			inline static Shader* s_LocalShader = nullptr;
		};
	}
}


#endif // !OE1_IV_SKYBOX_PREVIEW_RENDERER_H_
