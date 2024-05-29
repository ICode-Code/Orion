#include "TextureCubeMap.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	TextureCubeMap::TextureCubeMap(std::vector<DataBlock::Image2D> _source, std::string _name)
	{
		if (_source.size() != 6)
			return;

		m_Width = _source[0].Width;
		m_Height = _source[0].Height;

		m_Name = _name;

		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);

		for (int i = 0; i < 6; i++)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _source[i].Data);
		}
		
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		m_Valid = true;

		for (int i = 0; i < 6; i++)
			stbi_image_free(_source[i].Data);
	}
	TextureCubeMap::~TextureCubeMap()
	{
		glDeleteTextures(1, &m_Texture);
	}

	GLuint TextureCubeMap::GetTexture() const { return m_Texture; };
	GLuint TextureCubeMap::GetPreview() const { return m_Prview; };
	int TextureCubeMap::GetWidth() { return m_Width; };
	int TextureCubeMap::GetHeight() { return m_Height; };

	void TextureCubeMap::SetName(std::string _name)
	{
		m_Name = _name;
	}
	std::string TextureCubeMap::GetName() { return m_Name; }
	bool TextureCubeMap::Valid() { return m_Valid; }
}