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
	}
	void Window::Close()
	{
		m_Args.Running = false;
	}
	void Window::SetEventCallback(const EVENT_CALLBACK& _callback)
	{
		m_Callback = _callback;
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
		glfwSetWindowUserPointer(m_Args.Win, &m_Callback);
		RegisterEventCalls();
		SetClearColor();
	}
	void Window::RegisterEventCalls()
	{
		/// Window Resize

		glfwSetWindowSizeCallback(m_Args.Win, [](GLFWwindow* _window, int _width, int _height)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				WindowResizeEvent event(_width, _height);
				callback(event);
			});

		/// Window Close
		glfwSetWindowCloseCallback(m_Args.Win, [](GLFWwindow* _window)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				WindowCloseEvent e;
				callback(e);
			});


		/// Key Press
		glfwSetKeyCallback(m_Args.Win, [](GLFWwindow* _window, int _key, int _scan_code, int _action, int _mode)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				if (_action == GLFW_PRESS)
				{
					KeyPressedEvent e(_key, 0);
					callback(e);
				}
				else if (_action == GLFW_REPEAT)
				{
					KeyRepeatEvent e(_key, 1);
					callback(e);
				}
				else if (_action == GLFW_RELEASE)
				{
					KeyReleaseEvent e(_key);
					callback(e);
				}
			});


		/// Mouse Motion
		glfwSetCursorPosCallback(m_Args.Win, [](GLFWwindow* _window, double _xpos, double _ypos)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				MouseMovedEvent e(_xpos, _ypos);
				callback(e);
			});


		/// Mouse Scroll
		glfwSetScrollCallback(m_Args.Win, [](GLFWwindow* _window, double _xoffset, double _yoffset)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				MouseScrolledEvent e((float)_xoffset, (float)_yoffset);
				callback(e);
			});


		/// Mouse Key
		glfwSetMouseButtonCallback(m_Args.Win, [](GLFWwindow* _window, int _button, int _action, int _mods)
			{
				EVENT_CALLBACK& callback = *(EVENT_CALLBACK*)glfwGetWindowUserPointer(_window);

				if (_action == GLFW_PRESS)
				{
					MouseButtonPressedEvent e(_button);
					callback(e);
				}
				else if (_action == GLFW_RELEASE)
				{
					MouseButtonReleaseEvent e(_button);
					callback(e);
				}
			});

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