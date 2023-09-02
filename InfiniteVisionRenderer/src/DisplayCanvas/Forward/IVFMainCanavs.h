#ifndef OE1_IVF_MAIN_CANAVS_H_
#define OE1_IVF_MAIN_CANAVS_H_

#include "../IVFramebuffer/IVFramebuffer.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVFMainCanavs : public IVFramebuffer
		{
		public:
			IVFMainCanavs(const int _width, const int _height);
			IVFMainCanavs(const int _res[2]);
			virtual ~IVFMainCanavs();


			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _index) override;


		protected:
			GLuint m_Color;
			GLuint m_Depth;

		private: // util
			void SetBufferAttachment() override;

			
		};
	}
}

#endif // !OE1_IVF_MAIN_CANAVS_H_
