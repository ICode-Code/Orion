#ifndef OE1_FRAMEBUFFER_H_
#define OE1_FRAMEBUFFER_H_

#include <Log.h>
#include <GL/glew.h>
#include "DefaultFramebufferValue.h"
#include <glm/gtc/type_ptr.inl>


namespace OE1Core
{
	class Framebuffer
	{
	public:
		Framebuffer(int _width, int _height);
		Framebuffer(glm::ivec2 _res);
		Framebuffer(const Framebuffer&) = delete;
		virtual ~Framebuffer();


		virtual void Attach(bool _clean_buffer = true, GLenum _usage = GL_FRAMEBUFFER);
		// Bind Default
		virtual void Detach();
		virtual void Clear(GLbitfield _mask);
		virtual void SetClearColor(float _color[4] = nullptr);
		virtual void SetClearColor(std::initializer_list<float> _list);
		virtual void SetClearColor(glm::vec4 _color);
		virtual void SaveFrame(int _attachment_index, const char* _name);
		/// <summary>
		/// Create and bind the necessary color and depth attachment here
		/// !!!!! DO NOT GEN FRAMEBUFFER HERE IT IS ALREADY DONE IN BASE CLASS !!!!!!!!!!!!!!!!
		/// </summary>
		virtual void Init() = 0;
		virtual void Update(int _width, int _height) = 0;
		virtual GLuint GetAttachment(int _index) = 0;


		virtual int			Readi1(int _attachment_index, int _posX, int _posY);
		virtual glm::ivec4	Readi4(int _attachment_index, int _posX, int _posY);
		virtual glm::ivec3	Readi3(int _attachment_index, int _posX, int _posY);
		virtual glm::ivec2	Readi2(int _attachment_index, int _posX, int _posY);

		virtual float		Readf1(int _attachment_index, int _posX, int _posY);
		virtual glm::vec4	Readf4(int _attachment_index, int _posX, int _posY);
		virtual glm::vec3	Readf3(int _attachment_index, int _posX, int _posY);
		virtual glm::vec2	Readf2(int _attachment_index, int _posX, int _posY);

		int GetWidth() const;
		int GetHeight() const;

	protected:
		glm::vec4 m_ClearColor = glm::vec4(glm::vec3(0.1f), 1.0f);
		int m_Width;
		int m_Height;
		GLuint m_Framebuffer;
		GLbitfield m_CleanMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT;
	};
}

#endif // !OE1_FRAMEBUFFER_H_
