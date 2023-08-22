#ifndef OE1_MAIN_FDC_H_
#define OE1_MAIN_FDC_H_


#include "../../Framebuffer/Framebuffer.h"


namespace OE1Core
{
	class MainFDC : public Framebuffer
	{
	public:
		MainFDC(int _width, int _height);
		MainFDC(glm::ivec2 _res);
		virtual ~MainFDC();

		virtual void Update(int _width, int _height) override;
		virtual GLuint GetAttachment(int _index) override;

	protected:
		virtual void Init() override;
		void ApplyTextureFilter();

	protected:
		GLuint m_Color;
		GLuint m_RenderID;
		GLuint m_Depth;
	};
}

#endif // !OE1_MAIN_FDC_H_
