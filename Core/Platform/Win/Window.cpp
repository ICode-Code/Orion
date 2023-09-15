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
		InitRenderState();

		SetClearColor({0.05f, 0.05f, 0.05f, 1.0f});

	}
	Window::~Window()
	{
		SDL_DestroyWindow(m_Args.Win);
	}
	void Window::InitOpenGLContext()
	{
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	}
	void Window::InitRenderState()
	{
		// Depth
		glEnable(GL_DEPTH_TEST);

		// Stencil
		glEnable(GL_STENCIL_TEST);
		glStencilOp(GL_KEEP, GL_REPLACE, GL_REPLACE);

		// Blend operation
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	void Window::EnableWin()
	{
		// Make the OpenGL context current for the window
		SDL_GL_MakeCurrent(m_Args.Win, m_Args.Context);

		// Show the SDL window (if not already shown)
		SDL_ShowWindow(m_Args.Win);

		m_Args.Running = true;
	}
	void Window::DisableWin()
	{
		SDL_HideWindow(m_Args.Win);
	}
	void Window::Close()
	{
		m_Args.Running = false;
	}
	void Window::RegisterEventCallback(const EventCallback& _callback)
	{
		m_Callback = _callback;
	}
	void Window::RegisterImGuiSDLEventProcessorCallback(const EventPollCallback& _event_pull_callback)
	{
		m_EventPullCallback = _event_pull_callback;
	}
	SDL_Window* Window::GetWin()
	{
		return m_Args.Win;
	}
	WindowArg& Window::GetArg()
	{
		return m_Args;
	}
	void Window::InitWindow()
	{
		int number_of_display = SDL_GetNumVideoDisplays();
		if (number_of_display < 1)
		{
			LOG_ERROR("Unable to find a window display. The operation has been terminated.");
			SDL_Quit();
			exit(0);
		}

		// make sure we have propere size to init
		if (m_Args.Width == -1 || m_Args.Height == -1)
		{
			SDL_DisplayMode max_mode;
			SDL_GetDesktopDisplayMode(0, &max_mode);

			m_Args.Width = max_mode.w;
			m_Args.Height = max_mode.h - 50;
		}



		m_Args.Win = SDL_CreateWindow(m_Args.Name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Args.Width, m_Args.Height, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIDDEN);
		if (!m_Args.Win)
		{
			LOG_ERROR("Window creation failed, Operation terminated.");
			exit(0);
		}

		int b_left, b_right, b_top, b_bottom;
		SDL_GetWindowBordersSize(m_Args.Win, &b_top, &b_left, &b_bottom, &b_right);
		m_Args.Width -= (b_left + b_right);
		m_Args.Height -= (b_bottom + b_top);
		SDL_SetWindowSize(m_Args.Win, m_Args.Width, m_Args.Height);
		SDL_MaximizeWindow(m_Args.Win);

		m_Args.Context = SDL_GL_CreateContext(m_Args.Win);

		if (!m_Args.Context)
		{
			LOG_ERROR("OpenGL Context creation failed, Operation terminated.");
			exit(0);
		}

		SDL_SetWindowData(m_Args.Win, m_Args.UserDataKey, &m_Callback);
		RegisterEventCalls();
		SetClearColor();
	}
	void Window::RegisterEventCalls()
	{
		/// Window Resize

		SDL_SetEventFilter(
			[](void* user_data, SDL_Event* _event) -> int
			{
				Window* window_handler = static_cast<Window*>(user_data);


				if (_event->type == SDL_KEYDOWN)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::KeyPressedEvent e(_event->key.keysym.sym, 0);
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_KEYUP)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::KeyReleaseEvent e(_event->key.keysym.sym);
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_QUIT)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::WindowCloseEvent e;
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_WINDOWEVENT)
				{
					if (_event->window.event == SDL_WINDOWEVENT_MINIMIZED)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowMinimizedEvent e;
						_callback(e);
						return 1;
					}
					else if (_event->window.event == SDL_WINDOWEVENT_MAXIMIZED)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowMaximizedEvent e;
						_callback(e);
						return 1;
					}
					else if (_event->window.event == SDL_WINDOWEVENT_FOCUS_LOST)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowLossFocusEvent e;
						_callback(e);
						return 1;
					}
					else if (_event->window.event == SDL_WINDOWEVENT_FOCUS_GAINED)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowFocusedEvent e;
						_callback(e);
						return 1;
					}

					else if (_event->window.event == SDL_WINDOWEVENT_RESIZED)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowResizeEvent e(_event->window.data1, _event->window.data2);
						_callback(e);
						return 1;
					}

					else if (_event->window.event == SDL_WINDOWEVENT_MOVED)
					{
						EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
						OECore::WindowMovedEvent e;
						_callback(e);
						return 1;
					}
				}
				else if (_event->type == SDL_MOUSEMOTION)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::MouseMovedEvent e(_event->motion.xrel, _event->motion.yrel);
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_MOUSEBUTTONDOWN)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::MouseButtonPressedEvent e(_event->button.button);
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_MOUSEBUTTONUP)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::MouseButtonReleaseEvent e(_event->button.button);
					_callback(e);
					return 1;
				}
				else if (_event->type == SDL_MOUSEWHEEL)
				{
					EventCallback& _callback = *(EventCallback*)SDL_GetWindowData(window_handler->GetWin(), window_handler->GetArg().UserDataKey);
					OECore::MouseScrolledEvent e(static_cast<double>(_event->wheel.x), static_cast<double>(_event->wheel.y));
					_callback(e);
					return 1;
				}

				return 1;
			}, this);

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
	void Window::PullEvent()
	{
		while (SDL_PollEvent(&m_Args.SDL_Event))
		{
			m_EventPullCallback(&m_Args.SDL_Event);
		}

		m_CurrentTime = SDL_GetPerformanceCounter();
		m_Args.DeltaTime = ((float)(m_CurrentTime - m_LastFrameTime) / (float)SDL_GetPerformanceFrequency());
		m_LastFrameTime = m_CurrentTime;
	}
	void Window::SwapBuffer()
	{
		SDL_GL_SwapWindow(m_Args.Win);
	}
}