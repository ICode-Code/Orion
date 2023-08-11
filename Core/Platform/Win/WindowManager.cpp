#include "WindowManager.h"



namespace OE1Core
{
	WindowManager::WindowManager()
	{
		InitGLFW();
	}

	WindowManager::~WindowManager()
	{
		for (auto win : s_Windows)
			delete win.second;

		glfwTerminate();
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

		if (!s_HasValidContext)
		{
			s_HasValidContext = true;
			InitGLEW();
			ShowSystemLog();
		}

		return s_Windows[_name.c_str()];
	}
	void WindowManager::ShowSystemLog()
	{
		// Info
		LOG_INFO("Renderer: {0}", std::string((char*)glGetString(GL_RENDERER)));
		LOG_INFO("OpenglVersion: {0} - {1}", std::string((char*)glGetString(GL_VENDOR)), std::string((char*)glGetString(GL_VERSION)));
		LOG_INFO("GLSL_Version: {0}", std::string((char*)glGetString(GL_SHADING_LANGUAGE_VERSION)));
		LOG_INFO("GLEW_Version: {0}", std::string((char*)glewGetString(GLEW_VERSION)));
	}
}