#include "CoreEngine.h"


namespace OE1Core
{
	CoreEngine::CoreEngine(int argc, char** argv)
	{
		s_Window = OE1Core::WindowManager::RegisterWindow("Orion", 1366, 768);
		s_Window->EnableWin();
		s_Window->SetEventCallback(std::bind(&CoreEngine::OnEvent, this, std::placeholders::_1));
		s_GuiBase = new OE1Core::GUIBase(s_Window->GetWin());
		
	}

	CoreEngine::~CoreEngine()
	{
		delete s_GuiBase;
	}
	void CoreEngine::Run()
	{
		while (*s_Window)
		{


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
		s_Window->Close();
		return true;
	}
	bool CoreEngine::HandleWindowResizeEvent(WindowResizeEvent& e)
	{
		return true;
	}
}