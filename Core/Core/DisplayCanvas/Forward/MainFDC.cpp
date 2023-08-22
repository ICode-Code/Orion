#include "MainFDC.h"


namespace OE1Core
{
	MainFDC::MainFDC(int _width, int _height)
		: Framebuffer{_width, _height}
	{
		Init();
	}
	MainFDC::MainFDC(glm::ivec2 _res)
		: Framebuffer{ _res }
	{
		Init();
	}
	MainFDC::~MainFDC()
	{

	}
	void MainFDC::Update(int _width, int _height)
	{
		glDeleteTextures(1, &m_RenderID);
		glDeleteTextures(1, &m_Color);
		glDeleteRenderbuffers(1, &m_Depth);
	}
	GLuint MainFDC::GetAttachment(int _index)
	{
		return m_Color;
	}

	void MainFDC::Init()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

		glGenTextures(1, &m_Color);
		glGenTextures(1, &m_RenderID);

		glBindTexture(GL_TEXTURE_2D, m_RenderID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, m_Width, m_Height, 0, GL_RED_INTEGER, GL_UNSIGNED_BYTE, NULL);
		ApplyTextureFilter();

		glBindTexture(GL_TEXTURE_2D, m_Color);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RED_INTEGER, GL_FLOAT, NULL);
		ApplyTextureFilter();

		glGenRenderbuffers(1, &m_Depth);
		glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Width, m_Height);

		unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
		glDrawBuffers(2, attachments);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_RenderID, 0);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_Color, 0);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Depth);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			LOG_ERROR("Failed to complate framebuffer MainFDC");

		glBindRenderbuffer(GL_RENDERBUFFER, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void MainFDC::ApplyTextureFilter()
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
}