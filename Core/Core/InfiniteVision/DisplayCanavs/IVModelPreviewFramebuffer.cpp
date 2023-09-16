#include "IVModelPreviewFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVModelPreviewFramebuffer::IVModelPreviewFramebuffer(GLuint& _color)
			: IVForwardBaseFramebuffer{ IVFrameSize::R_1k }
		{
			Init(_color);
		}
		IVModelPreviewFramebuffer::~IVModelPreviewFramebuffer()
		{
			glDeleteRenderbuffers(1, &m_Depth);
		}
		void IVModelPreviewFramebuffer::SetBufferAttachment()
		{
		}
		void IVModelPreviewFramebuffer::Update(int _width, int _height)
		{
			
		}
		GLuint IVModelPreviewFramebuffer::GetAttachment(int _index)
		{
			return 0;
		}
		void IVModelPreviewFramebuffer::Init() {};
		void IVModelPreviewFramebuffer::Init(GLuint& _color)
		{
			// Color
			glGenTextures(1, &_color);
			glBindTexture(GL_TEXTURE_2D, _color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);


			// Attach to Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Depth);

			SetDrawBuffers(1);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IVModelPreviewFramebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}