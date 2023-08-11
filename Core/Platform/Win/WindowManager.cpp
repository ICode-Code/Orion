#include "WindowManager.h"



namespace OE1Core
{
	WindowManager::WindowManager()
	{
		InitGLFW();

		const char* engine_window_name = "Engine";
		s_Windows.insert(std::make_pair(engine_window_name, new Window(engine_window_name)));
		s_ActiveWindow = s_Windows[engine_window_name];
		InitGLEW();

		ShowLog();
		s_ActiveWindow->ShowWin();
	}

	WindowManager::~WindowManager()
	{
		for (auto win : s_Windows)
			delete win.second;

		glfwTerminate();
	}
	bool WindowManager::IsActiveWindowRunning()
	{
		return s_ActiveWindow->GetArg().Running;
	}

	void WindowManager::InitGLFW()
	{
		glfwInit();
	}
	void WindowManager::InitGLEW()
	{
		glewExperimental = GL_TRUE;

		auto init_glew = glewInit();

		if (init_glew != GLEW_OK)
		{
			LOG_ERROR("Failed to initilize GLEW: Operation terminated.");
			exit(0);
		}

	}
	Window* WindowManager::GetWindow(std::string _name)
	{
		if (s_Windows.find(_name) == s_Windows.end())
		{
			LOG_ERROR("No Window registed with the name {0}", _name);
			return nullptr;
		}
		return s_Windows[_name];
	}
	void WindowManager::PurgWindow(std::string _name)
	{
		if (s_Windows.find(_name) == s_Windows.end())
		{
			LOG_ERROR("Failed to Purge Window: No Window registed with the name {0}", _name);
			return;
		}

		s_Windows.erase(_name);
	}
	Window* WindowManager::RegisterWindow(std::string _name, int _width, int _height)
	{
		if (s_Windows.find(_name) != s_Windows.end())
		{
			LOG_ERROR("Failed to register new window: Window name already exists.");
			return nullptr;
		}

		s_Windows.insert(std::make_pair(_name.c_str(), new Window(_name.c_str(), _width, _height)));
		return s_Windows[_name.c_str()];
	}
	void WindowManager::SetWindowActive(std::string _name)
	{
		if (s_Windows.find(_name) == s_Windows.end())
		{
			LOG_ERROR("Failed to activate window: No Window registed with the name {0}", _name);
			return;
		}

		s_ActiveWindow = s_Windows[_name.c_str()];
		s_ActiveWindow->ShowWin();
		glfwMakeContextCurrent(s_ActiveWindow->GetWin());
	}
	void WindowManager::SetWindowActive(Window* _ptr)
	{
		s_ActiveWindow = _ptr;
		s_ActiveWindow->ShowWin();
		glfwMakeContextCurrent(s_ActiveWindow->GetWin());
	}
	void WindowManager::ShowLog()
	{
		// Info
		LOG_INFO("Renderer: {0}", std::string((char*)glGetString(GL_RENDERER)));
		LOG_INFO("OpenglVersion: {0} - {1}", std::string((char*)glGetString(GL_VENDOR)), std::string((char*)glGetString(GL_VERSION)));
		LOG_INFO("GLSL_Version: {0}", std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
		LOG_INFO("GLEW_Version: {0}", std::string((char*)glewGetString(GLEW_VERSION)));
	}
}