#ifndef OE1_IV_DEFFERED_MAIN_LIGHT_PASS_FRAMEBUFFER_H_
#define OE1_IV_DEFFERED_MAIN_LIGHT_PASS_FRAMEBUFFER_H_



#include "IVForwardBaseFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{
		class IVDefferedMainLightPassFramebuffer : public IVForwardBaseFramebuffer
		{
		public:
			IVDefferedMainLightPassFramebuffer(const int _width, const int _height);
			IVDefferedMainLightPassFramebuffer(const int _res[2]);
			virtual ~IVDefferedMainLightPassFramebuffer();

			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _idx) override;


		protected:
			GLuint m_Depth;

		public:
			GLuint m_Color;

		private:
			void SetBufferAttachment() override;
		};
	}
}

#endif // !OE1_IV_DEFFERED_MAIN_LIGHT_PASS_FRAMEBUFFER_H_
