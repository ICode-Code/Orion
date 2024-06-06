#include "IVBloom.h"
#include "../Core/Component/CameraComponent/CameraComponent.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVBloom::IVBloom()
		{
			m_Quad = new DS::Quad();

			m_UpSample = ShaderManager::GetShader(ShaderID::BLOOM_UP_SAMPLE);
			m_DownSample = ShaderManager::GetShader(ShaderID::BLOOM_DOWN_SAMPLE);
		}
		IVBloom::~IVBloom()
		{
			delete m_Quad;
		}

		void IVBloom::ApplyBloom(Component::CameraComponent* _camera)
		{
			_camera->PostProcessBloomFM()->Attach();

			glDisable(GL_BLEND);

			DownSamplePass(_camera);

			// Enbale Additive Blending
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glBlendEquation(GL_FUNC_ADD);

			UpSamplePass(_camera);

			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			_camera->PostProcessBloomFM()->Detach();
		}

		void IVBloom::DrawQuad()
		{
			glBindVertexArray(m_Quad->GetVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
		}

		void IVBloom::DownSamplePass(class Component::CameraComponent* _camera)
		{
			const auto& mip_chain = _camera->PostProcessBloomFM()->GetMipChain();
			glm::vec2 _src_rez(_camera->PostProcessBloomFM()->m_Width, _camera->PostProcessBloomFM()->m_Height);

			m_DownSample->Attach();
			m_DownSample->Set2f("srcResolution", _src_rez);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, _camera->LightFB()->GetAttachment(0));

			// Progressively downsample
			for (size_t i = 0; i < mip_chain.size(); i++)
			{
				const BloomMip& mip = mip_chain[i];
				glViewport(0, 0, mip.IntFrameSize.x, mip.IntFrameSize.y);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip.Texture, 0);

				DrawQuad();

				m_DownSample->Set2f("srcResolution", mip.FrameSize);
				m_DownSample->Set1i("mipLevel", (int)i);
				glBindTexture(GL_TEXTURE_2D, mip.Texture);
			}

			m_DownSample->Detach();
		}
		void IVBloom::UpSamplePass(class Component::CameraComponent* _camera)
		{
			const auto& mip_chain = _camera->PostProcessBloomFM()->GetMipChain();

			m_UpSample->Attach();
			m_UpSample->Set1f("filterRadius", 0.006f);

			for (size_t i = mip_chain.size() - 1; i > 0; i--)
			{
				const BloomMip& mip_A = mip_chain[i];
				const BloomMip& mip_B = mip_chain[i - 1];

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_2D, mip_A.Texture);

				glViewport(0, 0, mip_B.IntFrameSize.x, mip_B.IntFrameSize.y);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mip_B.Texture, 0);

				DrawQuad();
			}

			
			
			m_UpSample->Detach();
		}
	}
}