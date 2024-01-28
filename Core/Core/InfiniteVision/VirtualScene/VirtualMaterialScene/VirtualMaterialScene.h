#ifndef OE1_MATERIAL_SCENE_H_
#define OE1_MATERIAL_SCENE_H_

#include "../VirtualScene.h"
#include "../../DisplayCanavs/IVVirtualMaterialSceneFramebuffer.h"


namespace OE1Core
{
	class VirtualMaterialScene : public VirtualScene
	{
	public:
		VirtualMaterialScene(SDL_Window* _win);
		virtual ~VirtualMaterialScene();

		static void Render(class MasterMaterial* _material);

	private:
		inline static Renderer::IVVirtualMaterialSceneFramebuffer* m_VirtualMaterialSceneFramebuffer = nullptr;
		inline static struct ModelPkg* m_VirtualRenderMesh = nullptr;
	};
}

#endif // !OE1_MATERIAL_SCENE_H_
