#include "CoreEngine.h"


namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{
		s_Window = OE1Core::WindowManager::RegisterWindow(ENGINE_MAIN_WINDOW, 1366, 768);
		s_Window->EnableWin();
		s_Window->SetEventCallback(std::bind(&CoreEngine::OnEvent, this, std::placeholders::_1));
		s_ShaderManager = new OE1Core::ShaderManager();
		s_MemeoryManager = new Memory::UniformBlockManager();
		// Init ImGui
		s_GuiBase = new OE1Core::GUIBase(s_Window->GetWin());

		// Create Master Scene
		SceneManager::RegisterScene("MasterScene", new Scene(s_Window->GetWin()), true);

		// Init Core system
		s_CoreSystem = new OE1Core::CoreSystem();

		// Initialize Master Renderer
		s_MainSceneRenderer = new OE1Core::Renderer::IVRender(s_CoreSystem);
	}

	CoreEngine::~CoreEngine()
	{
		delete s_GuiBase;
		delete s_CoreSystem;
		delete s_MainSceneRenderer;
		delete s_ShaderManager;
		delete s_MemeoryManager;
	}
	void CoreEngine::Run()
	{
		while (*s_Window)
		{
			// any queued command will be executed here
			ExecutionHandler::__exe();


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