#ifndef OE1_TEXTURE_H_
#define OE1_TEXTURE_H_

#include <GL/glew.h>
#include "Util/DataBlock.h"

namespace OE1Core
{
	class Texture
	{
	public:
		// so don't even sweat bro
		Texture(DataBlock::Image2D _image_raw, bool _correct_gamma = false);
		// This constructo call stbi_image_free(...)
		// so don't even sweat bro
		Texture(DataBlock::ImageHDRI _image_raw_hdri);
		~Texture();

		GLuint GetTexture() const;
		std::string GetName() const;
		std::string GetSeed() const;
		std::string SetSeed(std::string _seed);
		int GetWidth() const;
		int GetHeight() const;
		float GetSizeMB() const;

		void RegisterAssociateMaterialOffset(uint32_t _offset);
		bool PurgeAssociateMaterialOffset(uint32_t _offset);
		bool HasAssociateMaterial(uint32_t _offset);
		std::vector<uint32_t>& AssociateMaterialOffset();

	protected:
		// Texture Uniquenes
		std::string m_Seed;
		GLuint m_Texture;
		int m_Width;
		int m_Height;
		float m_SizeMB;
		bool m_LoadedWithGamma;
		std::string m_Name;
		bool m_HasAssociateMaterial = false;
		std::vector<uint32_t> m_AssociateMaterialOffsets;
	};
}

#endif // !OE1_TEXTURE_H_
