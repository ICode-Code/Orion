#include "CoreEngine.h"

namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{

		///////////////////////// ORDER MATTER HERE SO DON'T FUCK IT UP ///////////////////////////
		
		s_ProjectManager = new ProjectManager();

		// Init Window System
		s_Window = OE1Core::WindowManager::RegisterWindow(ENGINE_MAIN_WINDOW);
		
		// Setup the callback
		s_Window->RegisterEventCallback(std::bind(&CoreEngine::OnEvent, this, std::placeholders::_1));
		
		// Load compile all the Shader
		s_ShaderManager = new OE1Core::ShaderManager();

		// Init resource
		s_ResourceInitializer = new OE1Core::ResourceInitializer();

		// Init UI
		s_GuiBase = new OE1Core::GUIBase(s_Window->GetWin(), &s_Window->GetArg().MainContext);

		// Register ImGui Event Callabck
		s_Window->RegisterImGuiSDLEventProcessorCallback(std::bind(ImGui_ImplSDL2_ProcessEvent, std::placeholders::_1));

		// Init System Interface
		// This guys will be imporatnt whe  we have dynamic lib who want to interact with the core
		s_CoreSystem = new OE1Core::CoreSystem();
		s_SceneSystem = new OE1Core::SceneSystem();
		s_ShaderSystem = new OE1Core::ShaderSystem(); 

		// Buffer Manger
		s_MemeoryManager = new Memory::UniformBlockManager(s_ShaderSystem);

		// Create Master Scene
		SceneManager::RegisterScene("MasterScene", new Scene(s_Window->GetWin()), true);


		// command processing
		s_CommandExecutionHandleManager = new OE1Core::CommandHnd::ExeHandleManager(SceneManager::GetActiveScene());
	}

	CoreEngine::~CoreEngine()
	{
		delete s_ProjectManager;
		delete s_GuiBase;
		delete s_CoreSystem;
		delete s_SceneSystem;
		delete s_ShaderSystem;
		delete s_ShaderManager;
		delete s_MemeoryManager;
		delete s_ResourceInitializer;
		delete s_CommandExecutionHandleManager;
	}
	
	void CoreEngine::Run()
	{
		// Enbale the Window
		s_Window->EnableWin();

		ThreadPackage _pkg;
		_pkg.EngineWindow = s_Window;
		_pkg.SDLWindow = s_Window->GetArg().Win;
		_pkg.SharedContext = s_Window->GetArg().SharedContext;

		SDL_Thread* COMMAND_PROCESSING_THREAD = SDL_CreateThread(__exe_RunTimeCommandProcessingThread, "RunTimeCommand", &_pkg);

		while (s_Window->GetArg().Running)
		{
			s_Window->PullEvent();

			// any queued command will be executed here
			CommandHnd::ExeHandleManager::ProcessContextCommandQueue();
			
			SceneManager::UpdateScene(s_Window->GetArg().DeltaTime);

			SceneManager::RenderScenes();


			s_GuiBase->Attach();
			s_GuiBase->Update();
			s_GuiBase->Render(s_Window->GetWin(), s_Window->GetArg().MainContext);

			s_Window->SwapBuffer();
		}
		__TerminateSharedThread = !__TerminateSharedThread;
	}
	int CoreEngine::__exe_RunTimeCommandProcessingThread(void* _data)
	{
		ThreadPackage* pkg = static_cast<ThreadPackage*>(_data);

		int __thread_share = SDL_GL_MakeCurrent(pkg->EngineWindow->GetArg().Win, pkg->EngineWindow->GetArg().SharedContext);
		if (__thread_share != 0)
		{
			LOG_ERROR("Unable to Shader Context! Processing Low Frequency Command is not possible! aborting...");
			pkg->EngineWindow->Close();
			return 0;
		}

		while (!__TerminateSharedThread)
		{
			CommandHnd::ExeHandleManager::ProcessLowFrequencyCommands();


			SceneManager::GetActiveScene()->UpdateAnimationTransform();
			//std::this_thread::sleep_for(2s);
			
		}

		return 0;
	}

	void CoreEngine::OnEvent(OECore::IEvent& e) 
	{
		// Create dispacther and dispatch event
		OECore::IEventDispatcher event_dispatcher(e);

		// handle close window event right here
		event_dispatcher.Dispatch<OECore::WindowCloseEvent>(std::bind(&CoreEngine::HandleWindowCloseEvent, this, std::placeholders::_1));
		
		// Resize Event
		event_dispatcher.Dispatch<OECore::WindowResizeEvent>(std::bind(&CoreEngine::HandleWindowResizeEvent, this, std::placeholders::_1));

		// Key Event
		event_dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&CoreEngine::HandleApplicationKeyInput, this, std::placeholders::_1));

		// Maximized Event
		event_dispatcher.Dispatch<OECore::WindowMaximizedEvent>(std::bind(&CoreEngine::HandleWindowMax, this, std::placeholders::_1));


		// Minimized Event
		event_dispatcher.Dispatch<OECore::WindowMinimizedEvent>(std::bind(&CoreEngine::HandleWindowMin, this, std::placeholders::_1));

		if(!e.Handled())
			s_GuiBase->OnEvent(e);
		if (!e.Handled())
			SceneManager::OnEvent(e);
	}
	bool CoreEngine::HandleWindowCloseEvent(OECore::WindowCloseEvent& e)
	{
		CloseWin::s_ShouldOpen = !CloseWin::s_ShouldOpen;
		return true;
	}
	bool CoreEngine::HandleWindowResizeEvent(OECore::WindowResizeEvent& e)
	{
		return false;
	}
	bool CoreEngine::HandleWindowMax(OECore::WindowMaximizedEvent& e)
	{
		return false;
	}
	bool CoreEngine::HandleWindowMin(OECore::WindowMinimizedEvent& e)
	{
		return false;
	}
	bool CoreEngine::HandleApplicationKeyInput(OECore::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == SDLK_F11)
		{
			if (s_Window->GetArg().Maximized)
			{
				SDL_RestoreWindow(s_Window->GetWin()); 
				SDL_SetWindowFullscreen(s_Window->GetWin(), SDL_WINDOW_MAXIMIZED);
			}
			else
				SDL_SetWindowFullscreen(s_Window->GetWin(), SDL_WINDOW_FULLSCREEN_DESKTOP);

			s_Window->GetArg().Maximized = !s_Window->GetArg().Maximized;

			return true;
		}

		return false;
	}
}