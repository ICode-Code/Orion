#ifndef  OE1_MIN_TEXTURE_FILTER_H_
#define OE1_MIN_TEXTURE_FILTER_H_

#include "BaseMiniWindw.h"


namespace OE1Core
{
	class MinTextureFilterWin : public BaseMiniWindow
	{
	public:
		MinTextureFilterWin();
		virtual ~MinTextureFilterWin();

		virtual void Render() override;
		virtual void Update() override;

		// Open window
		static void Open();
		// Close window
		static void Close();

		static bool IsOpen();
	private:
		inline static bool s_ShouldOpen = false;
		ImVec2 m_LocalSize;
		const inline static int s_TextureNameFilterInputBufferSize = 256;
		inline static char s_TextureNameFilterInputBuffer[s_TextureNameFilterInputBufferSize];

	private:
		bool ImageWithName(GLuint _image, std::string _name, float _size = 0.0f);
	 };
}

#endif // ! OE1_MIN_TEXTURE_FILTER_H_
