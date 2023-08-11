#ifndef OE1_WINDOW_H_
#define OE1_WINDOW_H_

// orion
#include <Log.h> 


// gl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "WindowData.h"

namespace OE1Core
{
	class Window
	{
	public:
		Window(const char* _name = "Win", int _width = 1366, int _height = 768);
		~Window();

		GLFWwindow* GetWin();
		WindowArg& GetArg();
		inline operator bool() const { return m_Args.Running; };
		void SetClearColor(float _color[4] = nullptr);
		void SetClearColor(std::initializer_list<float> _list);
		void Update();
		void CleanDefaultBuffer();
		void SwapZDoubleBuffer();
		void EnableWin();
		void DisableWin();
		


	protected:
		void InitOpenGLContext();
		void InitWindow();

	protected:
		WindowArg m_Args;

	};
}


#endif // !OE1_WINDOW_H_
