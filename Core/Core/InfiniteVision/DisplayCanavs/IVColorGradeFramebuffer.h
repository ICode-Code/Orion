#ifndef OE1_IV_COLOR_GRADE_FRAMEBUFFER_H_
#define OE1_IV_COLOR_GRADE_FRAMEBUFFER_H_



#include "IVForwardBaseFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVColorGradeFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IVColorGradeFramebuffer(const int _width, const int _height);
			IVColorGradeFramebuffer(const int _res[2]);
			virtual ~IVColorGradeFramebuffer();

			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _idx) override;

		private:
			GLuint m_Color;
			GLuint m_Depth;

		private:
			void SetBufferAttachment() override;
		};
	}
}

#endif // !OE1_IV_COLOR_GRADE_FRAMEBUFFER_H_
