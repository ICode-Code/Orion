#ifndef OE1_IV_VIRTUAL_MATERIAL_SCENE_FRAMEBUFFER_H_
#define OE1_IV_VIRTUAL_MATERIAL_SCENE_FRAMEBUFFER_H_

#include  "IVForwardBaseFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVVirtualMaterialSceneFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IVVirtualMaterialSceneFramebuffer(GLuint& color);
			virtual ~IVVirtualMaterialSceneFramebuffer();

			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _idx) override;

			void SetBufferAttachment() override;

		private:
			GLuint m_Depth;

		private:
			void Init(GLuint& _color);

		};
	}
}
#endif // !OE1_IV_VIRTUAL_MATERIAL_SCENE_FRAMEBUFFER_H_
