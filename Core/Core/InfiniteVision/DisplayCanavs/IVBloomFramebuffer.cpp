#include "IVBloomFramebuffer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVBloomFramebuffer::IVBloomFramebuffer(const int _width, const int _height)
			: IVForwardBaseFramebuffer{ _width, _height }
		{
			Init();
		}
		IVBloomFramebuffer::IVBloomFramebuffer(const int _res[2])
			: IVForwardBaseFramebuffer{ _res }
		{
			Init();
		}
		IVBloomFramebuffer::~IVBloomFramebuffer()
		{
			for (int i = 0; i < m_MipLevel; i++)
				glDeleteTextures(1, &m_MipChain[i].Texture);
		}
		void IVBloomFramebuffer::SetBufferAttachment()
		{
			

		}
		GLuint IVBloomFramebuffer::GetAttachment(int _idx)
		{
			return m_MipChain[0].Texture;
		}
		std::vector<BloomMip>& IVBloomFramebuffer::GetMipChain() { return m_MipChain; };
		void IVBloomFramebuffer::UpdateMipLevel(int _mip_level)
		{
			if (_mip_level <= 1)
			{
				LOG_ERROR("Falied to update frame mip level! To Low Mip Level");
				return;
			}
			for (int i = 0; i < m_MipLevel; i++)
				glDeleteTextures(1, &m_MipChain[i].Texture);

			m_MipLevel = _mip_level;
			m_MipChain.clear();
			
			Init();
			Update(m_Width, m_Height);
		}
		void IVBloomFramebuffer::Update(int _width, int _height)
		{
			m_Width = _width;
			m_Height = _height;

			glm::vec2 mip_size((float)m_Width, (float)m_Height);
			glm::ivec2 mip_size_i(m_Width, m_Height);

			for (int i = 0; i < m_MipLevel; i++)
			{
				mip_size *= 0.5f;
				mip_size_i /= 2;

				m_MipChain[i].FrameSize = mip_size;
				m_MipChain[i].IntFrameSize = mip_size_i;

				glBindTexture(GL_TEXTURE_2D, m_MipChain[i].Texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, mip_size_i.x, mip_size_i.y, 0, GL_RGB, GL_FLOAT, nullptr);
			
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			}


			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_MipChain[0].Texture, 0);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		void IVBloomFramebuffer::Init()
		{
			
			m_MipChain.reserve(m_MipLevel);
			glm::vec2 mip_size((float)m_Width, (float)m_Height);
			glm::ivec2 mip_size_i(m_Width, m_Height);

			for (int i = 0; i < m_MipLevel; i++)
			{
				BloomMip mip;


				mip_size *= 0.5f;
				mip_size_i /= 2;

				glGenTextures(1, &mip.Texture);
				glBindTexture(GL_TEXTURE_2D, mip.Texture);

				glTexImage2D(GL_TEXTURE_2D, 0, GL_R11F_G11F_B10F, mip_size_i.x, mip_size_i.y, 0, GL_RGB, GL_FLOAT, nullptr);

				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

				m_MipChain.emplace_back(mip);
			}

			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_MipChain[0].Texture, 0);
		
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LogError("IVBloomFramebuffer");
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}