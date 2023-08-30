#ifndef OE1_IV_FRAMEBUFFER_H_
#define OE1_IV_FRAMEBUFFER_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Log.h>

#include <vector>


namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) IVFramebuffer
		{
		public:
			IVFramebuffer(int _width, int _he34ight);
			IVFramebuffer(int _res[2]);
			virtual ~IVFramebuffer();


			virtual void Attach(bool _clean_buffer = true, GLenum _usnage = GL_FRAMEBUFFER);

			// Bind Defualt 
			virtual void Detach();
			virtual void Clean(GLbitfield _mask);
			virtual void SetClearColor(float _color[4] = nullptr);
			// only read the first 4 digit
			virtual void SetClearColor(std::initializer_list<float> _list);
			virtual void SetClearColor(glm::vec4 _color);
			virtual void SaveFrame(int _attachment_index, const char* _name);



			virtual void Init() = 0;
			virtual void Update(int _width, int _height) = 0;
			virtual GLuint GetAttachment(int _index) = 0;



			virtual int			Readi1(int _attachment_index, int _posX, int posY);
			virtual glm::ivec4	Readi4(int _attachment_index, int _posX, int posY);
			virtual glm::ivec3	Readi3(int _attachment_index, int _posX, int posY);
			virtual glm::ivec2	Readi2(int _attachment_index, int _posX, int posY);


			virtual float		Read1f(int _attachment_index, int _posX, int posY);
			virtual glm::vec4	Readf4(int _attachment_index, int _posX, int posY);
			virtual glm::vec3	Readf3(int _attachment_index, int _posX, int posY);
			virtual glm::vec2	Readf2(int _attachment_index, int _posX, int posY);


			int GetWidth() const;
			int GetHeight() const;

		protected:
			float m_ClearColor[4] = {0.1f, 0.1f, 0.1f, 1.0f};
			int m_Width;
			int m_Height;
			GLuint m_Framebuffer;
			GLbitfield m_CleanMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;


		protected: // util
			virtual void SetBufferAttachment() = 0;
			// Do this after attaching framebuffer
			void LogError(std::string _buffer_name);
			void SetDrawBuffers(int _count);
			void DefaultTextureFilter();
			template<typename T> T ReadPixelData(int _attach_index, int _posX, int _posY, int _sizeX, int _sizeY, GLenum _data_format, GLenum _data_type);
		}; 

		template<typename T> T IVFramebuffer::ReadPixelData(int _attach_index, int _posX, int _posY, int _sizeX, int _sizeY, GLenum _data_format, GLenum _data_type)
		{
			T pixel_value;
			glBindFramebuffer(GL_READ_FRAMEBUFFER, m_Framebuffer);
			glReadBuffer(GL_COLOR_ATTACHMENT0 + _attach_index);
			glReadPixels(_posX, _posY, _sizeX, _sizeY, _data_format, _data_type, &pixel_value);
			return pixel_value;
		}
	}
}


#endif // !OE1_IV_FRAMEBUFFER_H_
