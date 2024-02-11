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
		m_SizeMB = 0.0f;

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
		m_SizeMB = 0.0f;

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
	float Texture::GetSizeMB() const
	{
		return m_SizeMB;
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

	void Texture::RegisterAssociateMaterialOffset(uint32_t _offset)
	{
		if (HasAssociateMaterial(_offset))
			return;
		m_AssociateMaterialOffsets.push_back(_offset);
	}
	bool Texture::PurgeAssociateMaterialOffset(uint32_t _offset)
	{
		if (HasAssociateMaterial(_offset))
			return false;

		size_t _puge_index = -1;

		for (size_t i = 0; i < m_AssociateMaterialOffsets.size(); i++)
		{
			if (m_AssociateMaterialOffsets[i] == _offset)
			{
				_puge_index = i;
				break;
			}
		}

		if (_puge_index == -1)
			return false;

		m_AssociateMaterialOffsets.erase(m_AssociateMaterialOffsets.begin() + _puge_index);
		return true;
	}
	bool Texture::HasAssociateMaterial(uint32_t _offset)
	{
		for (size_t i = 0; i < m_AssociateMaterialOffsets.size(); i++)
			if (m_AssociateMaterialOffsets[i] == _offset)
				return true;
		return false;
	}
	std::vector<uint32_t>& Texture::AssociateMaterialOffset()
	{
		return m_AssociateMaterialOffsets;
	}
}