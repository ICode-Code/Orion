#include "CoreEngine.h"


namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{

		///////////////////////// ORDER MATTER HERE SO DON'T FUCK IT UP ///////////////////////////
		CreateDefaultProjectDir();

		// Init Window System
		s_Window = OE1Core::WindowManager::RegisterWindow(ENGINE_MAIN_WINDOW, 1366, 768);
		
		

		// Setup the callback
		s_Window->SetEventCallback(std::bind(&CoreEngine::OnEvent, this, std::placeholders::_1));
		
		// Load compile all the Shader
		s_ShaderManager = new OE1Core::ShaderManager();

		// Init resource
		s_ResourceInitializer = new OE1Core::ResourceInitializer();

		// Init UI
		s_GuiBase = new OE1Core::GUIBase(s_Window->GetWin());


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
			// any queued command will be executed here
			ExecutionHandler::ProcessQueueCommands();

			SceneManager::UpdateScene(s_Window->GetArg().DeltaTime);
			s_MainSceneRenderer->RenderScene();




			s_Window->CleanDefaultBuffer();

			s_GuiBase->Attach();
			s_GuiBase->Update();
			s_GuiBase->Render();

			s_Window->SwapZDoubleBuffer();
		}
	}

	void CoreEngine::OnEvent(Event& e) 
	{
		// Create dispacther and dispatch event
		EventDispatcher event_dispatcher(e);

		// handle close window event right here
		event_dispatcher.Dispatch<WindowCloseEvent>(std::bind(&CoreEngine::HandleWindowCloseEvent, this, std::placeholders::_1));

		// and also Resize Event
		event_dispatcher.Dispatch<WindowResizeEvent>(std::bind(&CoreEngine::HandleWindowResizeEvent, this, std::placeholders::_1));

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
	bool CoreEngine::HandleWindowCloseEvent(WindowCloseEvent& e)
	{
		CloseWin::s_ShouldOpen = !CloseWin::s_ShouldOpen;
		return true;
	}
	bool CoreEngine::HandleWindowResizeEvent(WindowResizeEvent& e)
	{
		return true;
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