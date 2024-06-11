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

			glDeleteTextures(1, &m_Position);
			glDeleteTextures(1, &m_Normal);
			glDeleteTextures(1, &m_MetalRougnessAOAlpha);
			glDeleteTextures(1, &m_Emission);
			glDeleteTextures(1, &m_Rdepth);
		}
		void IVForwardMainPassFramebuffer::SetBufferAttachment()
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Color, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_UID, 0);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, m_Position, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, m_Normal, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, m_MetalRougnessAOAlpha, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, m_Emission, 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, m_Rdepth, 0);


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

			// COLOR
			glBindTexture(GL_TEXTURE_2D, m_Color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// ID
			glBindTexture(GL_TEXTURE_2D, m_UID);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Width, m_Height, 0, GL_RED_INTEGER, GL_INT, NULL);

			// POSITION
			glBindTexture(GL_TEXTURE_2D, m_Position);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// NORMAL
			glBindTexture(GL_TEXTURE_2D, m_Normal);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// METAL, ROUGHNESS, AO and ALPHA
			glBindTexture(GL_TEXTURE_2D, m_MetalRougnessAOAlpha);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// EMISSION
			glBindTexture(GL_TEXTURE_2D, m_Emission);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);

			// DEPTH
			glBindTexture(GL_TEXTURE_2D, m_Rdepth);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);


			// DEPTH
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, m_Width, m_Height);

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


			// Position
			glGenTextures(1, &m_Position);
			glBindTexture(GL_TEXTURE_2D, m_Position);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// Normal
			glGenTextures(1, &m_Normal);
			glBindTexture(GL_TEXTURE_2D, m_Normal);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// METAL_ROUGHNESS_AO_ALPHA
			glGenTextures(1, &m_MetalRougnessAOAlpha);
			glBindTexture(GL_TEXTURE_2D, m_MetalRougnessAOAlpha);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();


			// Emission
			glGenTextures(1, &m_Emission);
			glBindTexture(GL_TEXTURE_2D, m_Emission);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();


			glGenTextures(1, &m_Rdepth);
			glBindTexture(GL_TEXTURE_2D, m_Rdepth);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();


			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH32F_STENCIL8, m_Width, m_Height);


			// Attach to Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			SetBufferAttachment();

			SetDrawBuffers(7);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IVFMainCanavs");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}