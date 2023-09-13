#include "CoreEngine.h"

namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{

		///////////////////////// ORDER MATTER HERE SO DON'T FUCK IT UP ///////////////////////////
		CreateDefaultProjectDir();

		// Init Window System
		s_Window = OE1Core::WindowManager::RegisterWindow(ENGINE_MAIN_WINDOW);
		
		

		// Setup the callback
		s_Window->RegisterEventCallback(std::bind(&CoreEngine::OnEvent, this, std::placeholders::_1));
		
		// Load compile all the Shader
		s_ShaderManager = new OE1Core::ShaderManager();

		// Init resource
		s_ResourceInitializer = new OE1Core::ResourceInitializer();

		// Init UI
		s_GuiBase = new OE1Core::GUIBase(s_Window->GetWin(), &s_Window->GetArg().Context);

		// Register ImGui Event Callabck
		s_Window->RegisterImGuiSDLEventProcessorCallback(std::bind(ImGui_ImplSDL2_ProcessEvent, std::placeholders::_1));

		// Init System Interface
		s_CoreSystem = new OE1Core::CoreSystem();
		s_SceneSystem = new OE1Core::SceneSystem();
		s_ShaderSystem = new OE1Core::ShaderSystem();

		// Buffer Manger
		s_MemeoryManager = new Memory::UniformBlockManager(s_ShaderSystem);

		// Create Master Scene
		SceneManager::RegisterScene("MasterScene", new Scene(s_Window->GetWin()), true);

		// Initialize Master Renderer
		s_MainSceneRenderer = new OE1Core::Renderer::IVRender(s_SceneSystem, s_CoreSystem);

		CleanVirtualAsset(ORI_ACTIVE_PATH);
	}

	CoreEngine::~CoreEngine()
	{
		CleanVirtualAsset(ORI_ACTIVE_PATH);

		delete s_GuiBase;
		delete s_CoreSystem;
		delete s_SceneSystem;
		delete s_ShaderSystem;
		delete s_MainSceneRenderer;
		delete s_ShaderManager;
		delete s_MemeoryManager;
		delete s_ResourceInitializer;

	}
	
	void CoreEngine::Run()
	{
		// Enbale the Window
		s_Window->EnableWin();

		while (*s_Window)
		{
			s_Window->PullEvent();

			// any queued command will be executed here
			ExecutionHandler::ProcessQueueCommands();
			
			SceneManager::UpdateScene(s_Window->GetArg().DeltaTime);
			s_MainSceneRenderer->RenderScene();


			s_GuiBase->Attach(&s_Window->GetArg().SDL_Event);
			s_GuiBase->Update();
			s_GuiBase->Render(s_Window->GetWin(), s_Window->GetArg().Context);

			s_Window->SwapBuffer();
		}
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


		SceneManager::OnEvent(e);
	}
	void CoreEngine::CreateDefaultProjectDir()
	{
		PWSTR my_documents_path = nullptr;
		if (SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &my_documents_path) == S_OK)
		{
			std::wstring project_folder_path = my_documents_path;
			CoTaskMemFree(my_documents_path);

			project_folder_path += ORI_PROJECT_ROOT_PATH;

			if (!PathFileExists(project_folder_path.c_str()))
			{
				if (!CreateDirectoryW(project_folder_path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
				{
					LOG_ERROR("Failed to create ROOT folder");
				}
			}

			// Create Project folder
			project_folder_path += L"\\PRJ_Pilot";
			if (!PathFileExists(project_folder_path.c_str()))
			{
				if (!CreateDirectoryW(project_folder_path.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
				{
					LOG_ERROR("Failed to create PROJECT folder");
				}
			}
			ORI_ACTIVE_PROJECT_ROOT = project_folder_path;
			std::string _root = WideStrToNarrowStr(ORI_ACTIVE_PROJECT_ROOT);
			InitializeDirectoryHierarchy(_root + "\\");
		}
	}
	bool CoreEngine::HandleWindowCloseEvent(OECore::WindowCloseEvent& e)
	{
		CloseWin::s_ShouldOpen = !CloseWin::s_ShouldOpen;
		return true;
	}
	bool CoreEngine::HandleWindowResizeEvent(OECore::WindowResizeEvent& e)
	{

		return true;
	}
	bool CoreEngine::HandleWindowMax(OECore::WindowMaximizedEvent& e)
	{
		s_Window->GetArg().Running = true;
		return true;
	}
	bool CoreEngine::HandleWindowMin(OECore::WindowMinimizedEvent& e)
	{
		s_Window->GetArg().Running = false;
		return true;
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
	void CoreEngine::InitializeDirectoryHierarchy(std::string _root)
	{
		std::filesystem::create_directories(_root + "Assets");
		std::filesystem::create_directories(_root + "Assets\\Meshes");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Characters");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Environment");
		std::filesystem::create_directories(_root + "Assets\\Meshes\\Weapons");
		std::filesystem::create_directories(_root + "Assets\\Audio");
		std::filesystem::create_directories(_root + "Assets\\Audio\\Music");
		std::filesystem::create_directories(_root + "Assets\\Audio\\SoundFX");
		std::filesystem::create_directories(_root + "Assets\\Textures");
		std::filesystem::create_directories(_root + "Assets\\Textures\\Characters");
		std::filesystem::create_directories(_root + "Assets\\Textures\\Environment");
		std::filesystem::create_directories(_root + "Assets\\Textures\\UI");
		std::filesystem::create_directories(_root + "Assets\\Scripts");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\AI");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\Gameplay");
		std::filesystem::create_directories(_root + "Assets\\Scripts\\UI");
		std::filesystem::create_directories(_root + "Assets\\Prefabs");
		std::filesystem::create_directories(_root + "Assets\\Materials");
		std::filesystem::create_directories(_root + "Assets\\Shaders");
		std::filesystem::create_directories(_root + "Scenes");
		std::filesystem::create_directories(_root + "Scripts");
		std::filesystem::create_directories(_root + "Plugins");
		std::filesystem::create_directories(_root + "Build");
	}
	void CoreEngine::CleanVirtualAsset(std::string _dir)
	{
		for (auto iter : std::filesystem::directory_iterator(_dir))
		{
			if (iter.is_directory())
				CleanVirtualAsset(_dir + "\\" + iter.path().stem().string());

			std::filesystem::remove_all(iter.path());
		}


		InitializeDirectoryHierarchy(WideStrToNarrowStr(ORI_ACTIVE_PROJECT_ROOT) + "\\");
	}
}