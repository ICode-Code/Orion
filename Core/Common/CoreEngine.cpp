#include "CoreEngine.h"


namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{

		///////////////////////// ORDER MATTER HERE SO DON'T FUCK IT UP ///////////////////////////

		CreateDefaultProjectDir();

		// Init Window System
		s_Window = OE1Core::WindowManager::RegisterWindow(ENGINE_MAIN_WINDOW, 1366, 768);
		
		// Enbale the Window
		s_Window->EnableWin();

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
	}

	CoreEngine::~CoreEngine()
	{
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
		while (*s_Window)
		{
			// any queued command will be executed here
			ExecutionHandler::__exe();

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

			project_folder_path += s_ProjectRoot;

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
}