#ifndef OE1_MODEL_PREVIEW_FRAMEBUFFER_H_
#define OE1_MODEL_PREVIEW_FRAMEBUFFER_H_

#include "IVForwardBaseFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVModelPreviewFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IVModelPreviewFramebuffer(GLuint& _color);
			virtual ~IVModelPreviewFramebuffer();


			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _index) override;


		protected:
			GLuint m_Depth;

		private: // util
			void SetBufferAttachment() override;
			void Init(GLuint& _color);
		};
	}
}

#endif // !OE1_MODEL_PREVIEW_FRAMEBUFFER_H_
