#include "EngineWindow.h"

namespace OE1Core
{
	EngineWindow::EngineWindow(SDL_Event* _event)
		: BaseWindow{ _event, "OrionX", nullptr, 1366, 768} // start full screen
	{
		m_Callback = std::bind(&EngineWindow::OnEvent, this, std::placeholders::_1);
	}
	EngineWindow::~EngineWindow()
	{
		SDL_GL_DeleteContext(m_Args.MainContext);
		SDL_GL_DeleteContext(m_Args.SharedContext);
		SDL_DestroyWindow(m_Args.Win);
	}
	void EngineWindow::SetCloseTrigger(bool* _val)
	{
		m_CloseTrigger = _val;
	}
	void EngineWindow::ResetCallbacks()
	{
		m_Callback = std::bind(&EngineWindow::OnEvent, this, std::placeholders::_1);
		this->RegisterEventCalls();
	}
	void EngineWindow::OnEvent(OECore::IEvent& e)
	{
		OECore::IEventDispatcher event_dispatcher(e);

		event_dispatcher.Dispatch<OECore::WindowCloseEvent>(std::bind(&EngineWindow::HandleWindowCloseEvent, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowResizeEvent>(std::bind(&EngineWindow::HandleWindowResizeEvent, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&EngineWindow::HandleApplicationKeyInput, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowMaximizedEvent>(std::bind(&EngineWindow::HandleWindowMax, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowMinimizedEvent>(std::bind(&EngineWindow::HandleWindowMin, this, std::placeholders::_1));

		if(m_FollowUpEventCallback)
			m_FollowUpEventCallback(e);
	}

	bool EngineWindow::HandleWindowCloseEvent(OECore::WindowCloseEvent& e)
	{
		*m_CloseTrigger = true;
		return true;
	}
	bool EngineWindow::HandleWindowResizeEvent(OECore::WindowResizeEvent& e)
	{
		return false;
	}
	bool EngineWindow::HandleWindowMax(OECore::WindowMaximizedEvent& e)
	{
		return false;
	}
	bool EngineWindow::HandleWindowMin(OECore::WindowMinimizedEvent& e)
	{
		return false;
	}
	bool EngineWindow::HandleApplicationKeyInput(OECore::KeyPressedEvent& e)
	{
		if (e.GetKeyCode() == SDLK_F11)
		{
			if (m_Args.Maximized)
			{
				SDL_RestoreWindow(GetWin());
				SDL_SetWindowFullscreen(GetWin(), SDL_WINDOW_MAXIMIZED);
			}
			else
				SDL_SetWindowFullscreen(GetWin(), SDL_WINDOW_FULLSCREEN_DESKTOP);

			m_Args.Maximized = !m_Args.Maximized;

			return true;
		}


		return false;
	}
}