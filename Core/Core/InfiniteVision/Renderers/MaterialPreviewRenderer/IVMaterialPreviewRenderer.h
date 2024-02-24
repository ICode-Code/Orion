#ifndef OE1_IV_MATERIAL_PREVIEW_RENDERER
#define OE1_IV_MATERIAL_PREVIEW_RENDERER

#include "../IVBaseRenderer.h"
#include "../../DisplayCanavs/IVVirtualMaterialSceneFramebuffer.h"

namespace OE1Core
{
	class Scene;
	namespace Renderer
	{
		class IVMaterialPreviewRenderer : public IVBaseRenderer
		{
		public:
			IVMaterialPreviewRenderer();
			~IVMaterialPreviewRenderer();

			static void Render(MasterMaterial* _material, Scene* _scene);
			static void Refresh(MasterMaterial* _material, Scene* _scene);


		private:
			inline static Shader* s_LocalShader = nullptr;
			inline static struct IVModel* m_VirtualRenderMesh = nullptr;
		};
	}
}

#endif // !OE1_IV_MATERIAL_PREVIEW_RENDERER
