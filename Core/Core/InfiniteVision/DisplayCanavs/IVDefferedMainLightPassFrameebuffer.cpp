#include "IVDefferedMainLightPassFrameebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVDefferedMainLightPassFramebuffer::IVDefferedMainLightPassFramebuffer(const int _width, const int _height)
			: IVForwardBaseFramebuffer{_width, _height}
		{
			Init();
		}
		IVDefferedMainLightPassFramebuffer::IVDefferedMainLightPassFramebuffer(const int _res[2])
			: IVForwardBaseFramebuffer{_res}
		{
			Init();
		}

		IVDefferedMainLightPassFramebuffer::~IVDefferedMainLightPassFramebuffer()
		{
			glDeleteTextures(1, &m_Color);
			glDeleteRenderbuffers(1, &m_Depth);
		}

		void IVDefferedMainLightPassFramebuffer::SetBufferAttachment()
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Depth);
		}

		void IVDefferedMainLightPassFramebuffer::Update(int _width, int _height)
		{
			if (_width == m_Width && _height == m_Height)
				return;
			m_Width = _width;
			m_Height = _height;

			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
			glViewport(0, 0, m_Width, m_Height);

			// COLOR
			glBindTexture(GL_TEXTURE_2D, m_Color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// DEPTH
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);

			SetBufferAttachment();
		}

		GLuint IVDefferedMainLightPassFramebuffer::GetAttachment(int _index)
		{
			return m_Color;
		}

		void IVDefferedMainLightPassFramebuffer::Init()
		{
			// Color
			glGenTextures(1, &m_Color);
			glBindTexture(GL_TEXTURE_2D, m_Color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);


			// Attach to Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			SetBufferAttachment();

			SetDrawBuffers(1);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IVDefferedMainLightPassFramebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}