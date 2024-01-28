#include "IVVirtualMaterialSceneFramebuffer.h"
#include "LogUI.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVVirtualMaterialSceneFramebuffer::IVVirtualMaterialSceneFramebuffer(GLuint& _color)
			: IVForwardBaseFramebuffer{ IVFrameSize::R_1k }
		{
			Init(_color);
		
		}
		IVVirtualMaterialSceneFramebuffer::~IVVirtualMaterialSceneFramebuffer()
		{
			glDeleteTextures(1, &m_Depth);
		}
		void IVVirtualMaterialSceneFramebuffer::Init() { }
		void IVVirtualMaterialSceneFramebuffer::Update(int _width, int _height) {}
		GLuint IVVirtualMaterialSceneFramebuffer::GetAttachment(int _idx) { return 0; };
		void IVVirtualMaterialSceneFramebuffer::SetBufferAttachment() {  };
		void IVVirtualMaterialSceneFramebuffer::Init(GLuint& _color)
		{

			// Init Color tetxure
			glGenTextures(1, &_color);
			glBindTexture(GL_TEXTURE_2D, _color);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Width, m_Height, 0, GL_RGBA, GL_FLOAT, NULL);
			DefaultTextureFilter();

			// Depth
			glGenRenderbuffers(1, &m_Depth);
			glBindRenderbuffer(GL_RENDERBUFFER, m_Depth);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, m_Width, m_Height);

			// Attach Framebuffer
			glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_Depth);

			SetDrawBuffers(1);

			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				LOG_ERROR(LogLayer::Pipe("IVVirtualMaterialSceneFramebuffer is incomplete", OELog::CRITICAL));

			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}