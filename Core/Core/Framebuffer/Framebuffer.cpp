#include "Framebuffer.h"


namespace OE1Core
{
	Framebuffer::Framebuffer(int _width, int _height)
	{
		if ((_width < 1 || _height < 1) || (_width > 4096 || _height > 4096))
		{
			LOG_ERROR("Framebuffer Initialization Error: The provided framebuffer size is invalid.");
		}
		else
		{
			m_Width = _width;
			m_Height = _height;
			glGenFramebuffers(1, &m_Framebuffer);
		}	
	}
	Framebuffer::Framebuffer(glm::ivec2 _res)
	{
		if ((_res.x < 1 || _res.y < 1) || (_res.x > 4096 || _res.y > 4096))
		{
			LOG_ERROR("Framebuffer Initialization Error: The provided framebuffer size is invalid.");
		}
		else
		{
			m_Width = _res.x;
			m_Height = _res.y;
			glGenFramebuffers(1, &m_Framebuffer);
		}
	}
	Framebuffer::~Framebuffer()
	{
		glDeleteFramebuffers(1, &m_Framebuffer);
	}

	void Framebuffer::Attach(bool _clean_buffer, GLenum _usage)
	{
		glBindFramebuffer(_usage, m_Framebuffer);
		glViewport(0, 0, m_Width, m_Height);
		if (_clean_buffer)
		{
			glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
			glClear(m_CleanMask);
		}
	}
	void Framebuffer::Detach()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
	void Framebuffer::Clear(GLbitfield _mask)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
		glClearColor(m_ClearColor.x, m_ClearColor.y, m_ClearColor.z, m_ClearColor.w);
		glViewport(0, 0, m_Width, m_Height);
		glClear(_mask);
	}
	void Framebuffer::SetClearColor(float _color[4])
	{
		m_ClearColor.r = _color[0];
		m_ClearColor.g = _color[1];
		m_ClearColor.b = _color[2];
		m_ClearColor.a = _color[3];
	}
	void Framebuffer::SetClearColor(std::initializer_list<float> _list)
	{
		if (_list.size() < 4)
		{
			LOG_ERROR("Invalid framebuffer clear color!");
			return;
		}

		for (int i = 0; i < 4; i++)
			m_ClearColor[i] = *(_list.begin() + i);
	}
	void Framebuffer::SetClearColor(glm::vec4 _color)
	{
		m_ClearColor = _color;
	}
	void Framebuffer::SaveFrame(int _attachment_index, const char* _name)
	{

	}
	int Framebuffer::GetWidth() const { return m_Width; };
	int Framebuffer::GetHeight() const { return m_Height; };

	int	Framebuffer::Readi1(int _attachment_index, int _posX, int _posY)
	{
		int Pixel = 0;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RED_INTEGER,
			GL_INT,
			&Pixel
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return Pixel;
	}
	glm::ivec4	Framebuffer::Readi4(int _attachment_index, int _posX, int _posY)
	{
		glm::ivec4 pixel_value;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RGBA_INTEGER,
			GL_INT,
			glm::value_ptr(pixel_value)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
	glm::ivec3	Framebuffer::Readi3(int _attachment_index, int _posX, int _posY)
	{
		glm::ivec3 pixel_value;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RGB_INTEGER,
			GL_INT,
			glm::value_ptr(pixel_value)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
	glm::ivec2	Framebuffer::Readi2(int _attachment_index, int _posX, int _posY)
	{
		glm::ivec2 pixel_color;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RG_INTEGER,
			GL_INT,
			glm::value_ptr(pixel_color)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_color;
	}

	float Framebuffer::Readf1(int _attachment_index, int _posX, int _posY)
	{
		float pixel_value = 0;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_R32F,
			GL_FLOAT,
			&pixel_value
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
	glm::vec4	Framebuffer::Readf4(int _attachment_index, int _posX, int _posY)
	{
		glm::vec4 pixel_value;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RGBA16F,
			GL_FLOAT,
			glm::value_ptr(pixel_value)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
	glm::vec3	Framebuffer::Readf3(int _attachment_index, int _posX, int _posY)
	{
		glm::vec3 pixel_value;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RGB16F,
			GL_FLOAT,
			glm::value_ptr(pixel_value)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
	glm::vec2	Framebuffer::Readf2(int _attachment_index, int _posX, int _posY)
	{
		glm::vec2 pixel_value;
		glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
		glReadBuffer(GL_COLOR_ATTACHMENT0 + _attachment_index);
		glReadPixels(
			_posX,
			_posY,
			1,
			1,
			GL_RG16F,
			GL_FLOAT,
			glm::value_ptr(pixel_value)
		);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return pixel_value;
	}
}