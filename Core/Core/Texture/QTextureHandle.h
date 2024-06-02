#ifndef OE1_Q_TEXTURE_HANDLE_H_
#define OE1_Q_TEXTURE_HANDLE_H_

#include <GL/glew.h>
#include "Util/DataBlock.h"

namespace OE1Core
{
	class QTextureHandle
	{
	public:
		QTextureHandle(DataBlock::Image2D _data, bool _use_gamma = false);
		QTextureHandle(DataBlock::ImageHDRI _data);
		~QTextureHandle();


		GLuint GetTextureID();
		std::string GetName();

	private:
		GLuint m_TextureID = 0;
		bool m_Gamma = false;
		int m_Width = 0;
		int m_Height = 0;
		std::string m_Name = "";

	private: // Util
		void InitTexture(DataBlock::Image2D _data);
		void InitTexture(DataBlock::ImageHDRI _data);
	};
}

#endif // !OE1_Q_TEXTURE_HANDLE_H_
