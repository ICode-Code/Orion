#ifndef OE1_IV_FORWARD_MAIN_PASS_FRAMEBUFFER_H_
#define OE1_IV_FORWARD_MAIN_PASS_FRAMEBUFFER_H_



#include "IVForwardBaseFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVForwardMainPassFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IVForwardMainPassFramebuffer(const int _width, const int _height);
			IVForwardMainPassFramebuffer(const int _res[2]);
			virtual ~IVForwardMainPassFramebuffer();


			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _index) override;


		protected:
			GLuint m_Color;
			GLuint m_UID;
			GLuint m_Depth;

		private: // util
			void SetBufferAttachment() override;
		};
	}
}


#endif // !OE1_IV_FORWARD_MAIN_PASS_FRAMEBUFFER_H_
