#include "IVForwardMainPassFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVForwardMainPassFramebuffer::IVForwardMainPassFramebuffer(const int _width, const int _height)
			: IVForwardBaseFramebuffer{ _width, _height }
		{
			Init();
		}
		IVForwardMainPassFramebuffer::IVForwardMainPassFramebuffer(const int _res[2])
			: IVForwardBaseFramebuffer{ _res }
		{
			Init();
		}
		IVForwardMainPassFramebuffer::~IVForwardMainPassFramebuffer()
		{
			glDeleteTextures(1, &m_Color);
			glDeleteTextures(1, &m_UID);
			glDeleteRenderbuffers(1, &m_Depth);
		}
		void IVForwardMainPassFramebuffer::SetBufferAttachment()
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_UID, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Depth);
		}
		void IVForwardMainPassFramebuffer::Update(int _width, int _height)
		{
			if (_width == m_Width && _height == m_Height)
				return;
			m_Width = _width;
			m_Height = _height;

			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
			glViewport(0, 0, m_Width, m_Height);

			glBindTexture(GL_TEXTURE_2D, m_Color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			glBindTexture(GL_TEXTURE_2D, m_UID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Width, m_Height, 0, GL_RED_INTEGER, GL_INT, NULL);

			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);

			SetBufferAttachment();
		}
		GLuint IVForwardMainPassFramebuffer::GetAttachment(int _index)
		{
			return m_Color;
		}

		void IVForwardMainPassFramebuffer::Init()
		{
			// Color
			glGenTextures(1, &m_Color);
			glBindTexture(GL_TEXTURE_2D, m_Color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// UID
			glGenTextures(1, &m_UID);
			glBindTexture(GL_TEXTURE_2D, m_UID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Width, m_Height, 0, GL_RED_INTEGER, GL_INT, NULL);
			DefaultTextureFilter();

			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);


			// Attach to Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			SetBufferAttachment();

			SetDrawBuffers(2);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IVFMainCanavs");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}