#include "IV2DTextureArrayExtractorFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IV2DTextureArrayExtractorFramebuffer::IV2DTextureArrayExtractorFramebuffer(const int _width, const int _height, CheckMatPreviewTexture _texture)
			: IVForwardBaseFramebuffer{ _width, _height }
		{
			m_HasTextureX = _texture;
			Init();
		}
		IV2DTextureArrayExtractorFramebuffer::IV2DTextureArrayExtractorFramebuffer(const int _res[2], CheckMatPreviewTexture _texture)
			: IVForwardBaseFramebuffer{ _res }
		{
			m_HasTextureX = _texture;
			Init();
		}
		IV2DTextureArrayExtractorFramebuffer::~IV2DTextureArrayExtractorFramebuffer()
		{
			
			glDeleteTextures(1, &std::get<0>(m_Textures.Color));
			glDeleteTextures(1, &std::get<0>(m_Textures.Normal));
			glDeleteTextures(1, &std::get<0>(m_Textures.Metal));
			glDeleteTextures(1, &std::get<0>(m_Textures.Roughness));
			glDeleteTextures(1, &std::get<0>(m_Textures.MetalRougness));
			glDeleteTextures(1, &std::get<0>(m_Textures.Emission));
			glDeleteTextures(1, &std::get<0>(m_Textures.Alpha));
			glDeleteTextures(1, &std::get<0>(m_Textures.AO));

			glDeleteRenderbuffers(1, &m_Depth);
		}
		void IV2DTextureArrayExtractorFramebuffer::SetBufferAttachment()
		{
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, std::get<0>(m_Textures.Color), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, std::get<0>(m_Textures.Normal), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, std::get<0>(m_Textures.Metal), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, std::get<0>(m_Textures.Roughness), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, std::get<0>(m_Textures.MetalRougness), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT5, GL_TEXTURE_2D, std::get<0>(m_Textures.Emission), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT6, GL_TEXTURE_2D, std::get<0>(m_Textures.Alpha), 0);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT7, GL_TEXTURE_2D, std::get<0>(m_Textures.AO), 0);


			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Depth);
		}
		void IV2DTextureArrayExtractorFramebuffer::Update(int _width, int _height)
		{
			if (_width == m_Width && _height == m_Height)
				return;
			m_Width = _width;
			m_Height = _height;

			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
			glViewport(0, 0, m_Width, m_Height);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Color));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Normal));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Metal));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Roughness));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.MetalRougness));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Emission));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Alpha));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.AO));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);

			SetBufferAttachment();
		}
		GLuint IV2DTextureArrayExtractorFramebuffer::GetAttachment(int _index)
		{
			return 0;
		}

		void IV2DTextureArrayExtractorFramebuffer::Init()
		{
			FilterTextureIdx();

			glGenTextures(1, &std::get<0>(m_Textures.Color));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Color));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.Normal));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Normal));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.Metal));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Metal));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.Roughness));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Roughness));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.MetalRougness));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.MetalRougness));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.Emission));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Emission));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.Alpha));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.Alpha));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			glGenTextures(1, &std::get<0>(m_Textures.AO));
			glBindTexture(GL_TEXTURE_2D, std::get<0>(m_Textures.AO));
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
			DefaultTextureFilter();

			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Width, m_Height);


			// Attach to Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			SetBufferAttachment();

			SetDrawBuffers(8);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IV2DTextureArrayExtractorFramebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void IV2DTextureArrayExtractorFramebuffer::FilterTextureIdx()
		{
			m_DrawBuffers = 0;

			std::get<1>(m_Textures.Color) = m_DrawBuffers++;
			std::get<1>(m_Textures.Normal) = m_DrawBuffers++;
			std::get<1>(m_Textures.Metal) = m_DrawBuffers++;
			std::get<1>(m_Textures.Roughness) = m_DrawBuffers++;
			std::get<1>(m_Textures.MetalRougness) = m_DrawBuffers++;
			std::get<1>(m_Textures.Emission) = m_DrawBuffers++;
			std::get<1>(m_Textures.Alpha) = m_DrawBuffers++;
			std::get<1>(m_Textures.AO) = m_DrawBuffers++;
		}
	}
}