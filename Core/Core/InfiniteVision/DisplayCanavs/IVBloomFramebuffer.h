#ifndef OE1_IV_BLOOM_FRAMEBUFFER_H_
#define OE1_IV_BLOOM_FRAMEBUFFER_H_


#include "IVForwardBaseFramebuffer.h"

namespace OE1Core
{
	class PreferenceWin;
	namespace Renderer
	{
		struct BloomMip
		{
			glm::vec2 FrameSize = glm::vec2(0.0f);
			glm::ivec2 IntFrameSize = glm::ivec2(0);
			GLuint Texture;
		};
		class IVBloomFramebuffer : public IVForwardBaseFramebuffer
		{
			friend class IVBloom;
			friend class PreferenceWin;
		public:
			IVBloomFramebuffer(const int _width, const int _height);
			IVBloomFramebuffer(const int _res[2]);
			virtual ~IVBloomFramebuffer();

			void Init() override;
			void Update(int _width, int _height) override;
			GLuint GetAttachment(int _idx) override;
			void UpdateMipLevel(int _mip_level);
			std::vector<BloomMip>& GetMipChain();


		protected:
			std::vector<BloomMip> m_MipChain;
			int m_MipLevel = 5;

		private:
			void SetBufferAttachment() override;
		};
	}
}

#endif // !OE1_IV_BLOOM_FRAMEBUFFER_H_
