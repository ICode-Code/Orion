#include "QTextureHandle.h"
#include <STBI/stb_image.h>


namespace OE1Core
{
	QTextureHandle::QTextureHandle(DataBlock::Image2D _data, bool _load_gamma)
	{
		m_Gamma = _load_gamma;
		InitTexture(_data);
	}
	QTextureHandle::QTextureHandle(DataBlock::ImageHDRI _data)
	{
		InitTexture(_data);
	}
	QTextureHandle::~QTextureHandle()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	GLuint QTextureHandle::GetTextureID() { return m_TextureID; }
	std::string QTextureHandle::GetName() { return m_Name; }

	void QTextureHandle::InitTexture(DataBlock::Image2D _data)
	{
		m_Width = _data.Width;
		m_Height = _data.Height;
		m_Name = m_Name;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, m_Gamma ? GL_SRGB_ALPHA : GL_RGBA,
			m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.Data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_data.Data);
	}
	void QTextureHandle::InitTexture(DataBlock::ImageHDRI _data)
	{
		m_Width = _data.Width;
		m_Height = _data.Height;
		m_Name = m_Name;

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, m_Gamma ? GL_SRGB_ALPHA : GL_RGBA,
			m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _data.Data);


		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA16F,
			m_Width, m_Height,
			0, GL_RGBA,
			GL_FLOAT,
			_data.Data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);


		stbi_image_free(_data.Data);
	}
}