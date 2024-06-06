#ifndef OE1_IV_HDR_PREVIEW_RENDERER_H_
#define OE1_IV_HDR_PREVIEW_RENDERER_H_


#include "../IVBaseRenderer.h"
#include "../../DisplayCanavs/IVVirtualMaterialSceneFramebuffer.h"

namespace OE1Core
{
	class Scene;
	namespace Renderer
	{
		class IVHDRPreviewRenderer : public IVBaseRenderer
		{
		public:
			IVHDRPreviewRenderer();
			~IVHDRPreviewRenderer();

			static void Render(GLuint _src_hdri_texture, GLuint& _dest_preview_texture, Scene* _scene);

		private:
			inline static struct IVModel* m_VirtualRenderMesh = nullptr;
			inline static Shader* s_LocalShader = nullptr;
		};
	}
}


#endif // !OE1_IV_HDR_PREVIEW_RENDERER_H_
