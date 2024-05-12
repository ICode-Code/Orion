#include "GenesisWindow.h"
#include "../../Core/Scene/SceneManager.h"

namespace OE1Core
{
	GenesisWindow::GenesisWindow(SDL_Event* _event, SDL_GLContext _context)
		: BaseWindow{ _event, "Genesis", _context, 900, 600 } // start full screen
	{
		m_Callback = std::bind(&GenesisWindow::OnEvent, this, std::placeholders::_1);
	}
	GenesisWindow::~GenesisWindow()
	{
		SDL_GL_MakeCurrent(m_Args.Win, NULL);
		SDL_DestroyWindow(m_Args.Win);
	}
	void GenesisWindow::ResetCallbacks()
	{
		m_Callback = std::bind(&GenesisWindow::OnEvent, this, std::placeholders::_1);
		this->RegisterEventCalls();
	}
	void GenesisWindow::OnEvent(OECore::IEvent& e)
	{
		OECore::IEventDispatcher event_dispatcher(e);

		event_dispatcher.Dispatch<OECore::WindowCloseEvent>(std::bind(&GenesisWindow::HandleWindowCloseEvent, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowResizeEvent>(std::bind(&GenesisWindow::HandleWindowResizeEvent, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::KeyPressedEvent>(std::bind(&GenesisWindow::HandleApplicationKeyInput, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowMaximizedEvent>(std::bind(&GenesisWindow::HandleWindowMax, this, std::placeholders::_1));
		event_dispatcher.Dispatch<OECore::WindowMinimizedEvent>(std::bind(&GenesisWindow::HandleWindowMin, this, std::placeholders::_1));

		if (m_FollowUpEventCallback && !e.Handled())
			m_FollowUpEventCallback(e);
	}

	bool GenesisWindow::HandleWindowCloseEvent(OECore::WindowCloseEvent& e)
	{
		
		this->m_Args.Running = false;

		return true;
	}
	bool GenesisWindow::HandleWindowResizeEvent(OECore::WindowResizeEvent& e)
	{
		m_FrameSizeUpdateCallbak(e.GetWidth(), e.GetHeight());
		return true;
	}
	bool GenesisWindow::HandleWindowMax(OECore::WindowMaximizedEvent& e)
	{
		return true;
	}
	bool GenesisWindow::HandleWindowMin(OECore::WindowMinimizedEvent& e)
	{
		return true;
	}
	bool GenesisWindow::HandleApplicationKeyInput(OECore::KeyPressedEvent& e)
	{
		return true;
	}
}