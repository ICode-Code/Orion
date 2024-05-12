#include "WindowManager.h"



namespace OE1Core
{
	WindowManager::WindowManager()
	{
		InitSDL();

		s_EngineWindow = new EngineWindow(&s_Event);

		InitGLEW();
		ShowSystemLog();
	}

	WindowManager::~WindowManager()
	{
		if(s_GenesisWindow)
			delete s_GenesisWindow;

		delete s_EngineWindow;

		SDL_Quit();
	}

	void WindowManager::InitSDL()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			LOG_ERROR("Failed to Intialize SDL!");
			exit(0);
		}
	}
	void WindowManager::InitGLEW()
	{
		auto init_glew = glewInit();

		if (init_glew != GLEW_OK)
		{
			LOG_ERROR("Failed to initilize GLEW: Operation terminated.");
			exit(0);
		}

	}
	EngineWindow* WindowManager::GetEngineWindow() { return s_EngineWindow; }

	GenesisWindow* WindowManager::GetGenesisWindow() { return s_GenesisWindow; }
	GenesisWindow* WindowManager::IgniteGenesisWindow()
	{
		s_GenesisWindow = new GenesisWindow(&s_Event, s_EngineWindow->m_Args.MainContext);

		// Update State
		s_EngineWindow->m_Args.Playing = true;
		s_GenesisWindow->m_Args.Running = true;

		return s_GenesisWindow;
	}
	void WindowManager::DestroyGenesisWindow()
	{
		if (s_GenesisWindow)
		{
			// Update State
			s_EngineWindow->m_Args.Playing = false;

			s_GenesisWindow->Close();
			delete s_GenesisWindow;
			s_GenesisWindow = nullptr;
		}
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