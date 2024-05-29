#ifndef OE1_TEXTURE_CUBE_MAP_H_
#define OE1_TEXTURE_CUBE_MAP_H_


#include <GL/glew.h>
#include "Util/DataBlock.h"

namespace OE1Core
{
	class TextureCubeMap
	{
	public:
		TextureCubeMap(std::vector<DataBlock::Image2D> _source, std::string _name);
		~TextureCubeMap();

		GLuint GetTexture() const;
		GLuint GetPreview() const;
		int GetWidth();
		int GetHeight();

		void SetName(std::string _name);
		std::string GetName();
		bool Valid();

	protected:
		GLuint m_Texture = 0;
		GLuint m_Prview = 0;
		int m_Width = 0;
		int m_Height = 0;
		std::string m_Name;
		bool m_Valid = false;
	};
}



#endif // !OE1_TEXTURE_CUBE_MAP_H_
