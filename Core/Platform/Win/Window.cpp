#include "Window.h"


namespace OE1Core
{
	Window::Window(const char* _name, int _width, int _height)
	{
		m_Args.Name = _name;
		m_Args.Width = _width;
		m_Args.Height = _height;

		InitOpenGLContext();
		InitWindow();

	}
	Window::~Window()
	{
		glfwDestroyWindow(m_Args.Win);
	}
	void Window::InitOpenGLContext()
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

		glfwWindowHint(GLFW_VISIBLE, GL_FALSE); // dont show
	}
	void Window::EnableWin()
	{
		glfwMakeContextCurrent(m_Args.Win);
		glfwShowWindow(m_Args.Win);
		m_Args.Running = true;
	}
	void Window::DisableWin()
	{
		glfwHideWindow(m_Args.Win);
		m_Args.Running = false;
	}
	GLFWwindow* Window::GetWin()
	{
		return m_Args.Win;
	}
	WindowArg& Window::GetArg()
	{
		return m_Args;
	}
	void Window::InitWindow()
	{
		m_Args.Win = glfwCreateWindow(m_Args.Width, m_Args.Height, m_Args.Name, nullptr, nullptr);

		if (!m_Args.Win)
		{
			LOG_ERROR("Window creation failed, Operation terminated.");
			exit(0);
		}

		glfwMakeContextCurrent(m_Args.Win);
		SetClearColor();
	}

	void Window::Update()
	{

	}
	void Window::SetClearColor(float _color[4])
	{
		if (_color != nullptr)
		{
			m_Args.ClearColor[0] = _color[0];
			m_Args.ClearColor[1] = _color[1];
			m_Args.ClearColor[2] = _color[2];
			m_Args.ClearColor[3] = _color[3];
		}
		glClearColor(m_Args.ClearColor[0], m_Args.ClearColor[1], m_Args.ClearColor[2], m_Args.ClearColor[3]);
	}
	void Window::SetClearColor(std::initializer_list<float> _list)
	{
		if (_list.size() != 4)
		{
			LOG_ERROR("Expected 4 values for color representation.");
			glClearColor(m_Args.ClearColor[0], m_Args.ClearColor[1], m_Args.ClearColor[2], m_Args.ClearColor[3]);
			return;
		}

		for (size_t i = 0; i < _list.size(); i++)
			m_Args.ClearColor[i] = *(_list.begin() + i);
		
		glClearColor(m_Args.ClearColor[0], m_Args.ClearColor[1], m_Args.ClearColor[2], m_Args.ClearColor[3]);
	}
	void Window::CleanDefaultBuffer()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
		glfwPollEvents();
	}
	void Window::SwapZDoubleBuffer()
	{
		glfwSwapBuffers(m_Args.Win);
	}
}