#include "Texture.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	Texture::Texture(DataBlock::Image2D _image_raw, bool _correct_gamma)
	{
		m_Width	 = _image_raw.Width;
		m_Height = _image_raw.Height;
		m_Name = _image_raw.Name;
		m_LoadedWithGamma = _correct_gamma;


		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			m_LoadedWithGamma ? GL_SRGB_ALPHA : GL_RGBA,
			m_Width, m_Height,
			0, GL_RGBA,
			GL_UNSIGNED_BYTE,
			_image_raw.Data);

		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_image_raw.Data);
	}
	Texture::Texture(DataBlock::ImageHDRI _image_raw_hdri)
	{
		m_Width		= _image_raw_hdri.Width;
		m_Height	= _image_raw_hdri.Height;
		m_Name		= _image_raw_hdri.Name;
		m_LoadedWithGamma = false;

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_2D, m_Texture);

		glTexImage2D(
			GL_TEXTURE_2D, 0,
			GL_RGBA16F,
			m_Width, m_Height,
			0, GL_RGBA,
			GL_FLOAT,
			_image_raw_hdri.Data);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(_image_raw_hdri.Data);

	}
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_Texture);
	}

	GLuint Texture::GetTexture() const
	{
		return m_Texture;
	}
	std::string Texture::GetName() const
	{
		return m_Name;
	}
	int Texture::GetWidth() const
	{
		return m_Width;
	}
	int Texture::GetHeight() const
	{
		return m_Height;
	}
}