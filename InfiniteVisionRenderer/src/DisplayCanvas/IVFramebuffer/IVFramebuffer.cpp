#include "IVFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVFramebuffer::IVFramebuffer(int _width, int _height)
		{
			m_Width = _width;
			m_Height = _height;

			glGenFramebuffers(1, &m_Framebuffer);
		}
		IVFramebuffer::IVFramebuffer(int _res[2])
		{
			m_Width = _res[0];
			m_Height = _res[1];

			glGenFramebuffers(1, &m_Framebuffer);
		}
		IVFramebuffer::~IVFramebuffer()
		{
			glDeleteFramebuffers(1, &m_Framebuffer);
		}

		int IVFramebuffer::GetWidth() const { return m_Width; }
		int IVFramebuffer::GetHeight() const { return m_Height; }


		void IVFramebuffer::Attach(bool _clean_buffer, GLenum _usage)
		{
			glBindFramebuffer(_usage, m_Framebuffer);
			if (_clean_buffer)
				Clean(m_CleanMask);
		}

		// Bind Defualt
		void IVFramebuffer::Detach()
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void IVFramebuffer::Clean(GLbitfield _mask)
		{
			glClear(_mask);
		}
		void IVFramebuffer::SetClearColor(float _color[4])
		{
			for (int i = 0; i < 4; i++)
				m_ClearColor[i] = _color[i];
			glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);

		}
		// only read the first 4 digit
		void IVFramebuffer::SetClearColor(std::initializer_list<float> _list)
		{
			if (_list.size() < 4)
				return;

			for (int i = 0; i < 4; i++)
				m_ClearColor[i] = *(_list.begin() + i);
			glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);

		}
		void IVFramebuffer::SetClearColor(glm::vec4 _color)
		{
			for (int i = 0; i < 4; i++)
				m_ClearColor[i] = _color[i];
			glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]);
		}
		void IVFramebuffer::SaveFrame(int _attachment_index, const char* _name)
		{
			// do nothing for now
		}

		void IVFramebuffer::DefaultTextureFilter()
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}
		void IVFramebuffer::SetDrawBuffers(int _count)
		{
			std::vector<unsigned int> draw_buffers;
			for (int i = 0; i < _count; i++)
				draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
			glDrawBuffers(_count, draw_buffers.data());
		}
		void IVFramebuffer::LogError(std::string _buffer_name)
		{
			LOG_ERROR("Framebuffer -{0}- is not complate", _buffer_name);
		}


		int IVFramebuffer::Readi1(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<int>(
				_attachment_index, _posX, _posY, 1, 1, GL_RED_INTEGER, GL_INT);
		}
		glm::ivec4 IVFramebuffer::Readi4(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::ivec4>(
				_attachment_index, _posX, _posY, 1, 1, GL_RGBA_INTEGER, GL_INT);
		}
		glm::ivec3 IVFramebuffer::Readi3(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::ivec3>(_attachment_index, _posX, _posY, 1, 1, GL_RGB_INTEGER, GL_INT);
		}
		glm::ivec2 IVFramebuffer::Readi2(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::ivec2>(
				_attachment_index, _posX, _posY, 1, 1, GL_RG_INTEGER, GL_INT);
		}


		float IVFramebuffer::Read1f(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<float>(
				_attachment_index, _posX, _posY, 1, 1, GL_R32F, GL_FLOAT);
		}
		glm::vec4 IVFramebuffer::Readf4(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::vec4>(
				_attachment_index, _posX, _posY, 1, 1, GL_RGBA16F, GL_FLOAT);
		}
		glm::vec3 IVFramebuffer::Readf3(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::vec3>(
				_attachment_index, _posX, _posY, 1, 1, GL_RGB16F, GL_FLOAT);
		}
		glm::vec2 IVFramebuffer::Readf2(int _attachment_index, int _posX, int _posY)
		{
			return ReadPixelData<glm::vec2>(
				_attachment_index, _posX, _posY, 1, 1, GL_RG16F, GL_FLOAT);
		}
	}
}