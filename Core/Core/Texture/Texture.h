#ifndef OE1_TEXTURE_H_
#define OE1_TEXTURE_H_

#include <GL/glew.h>
#include "Util/DataBlock.h"

namespace OE1Core
{
	class Texture
	{
	public:
		// This constructo call stbi_image_free(...)
		// so don't even sweat bro
		Texture(DataBlock::Image2D _image_raw, bool _correct_gamma = false);
		// This constructo call stbi_image_free(...)
		// so don't even sweat bro
		Texture(DataBlock::ImageHDRI _image_raw_hdri);
		~Texture();

		GLuint GetTexture() const;
		std::string GetName() const;
		int GetWidth() const;
		int GetHeight() const;

	protected:
		GLuint m_Texture;
		int m_Width;
		int m_Height;
		bool m_LoadedWithGamma;
		std::string m_Name;
	};
}

#endif // !OE1_TEXTURE_H_
