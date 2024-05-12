#ifndef OE1_WINDOW_H_
#define OE1_WINDOW_H_

// orion
#include <Log.h> 
#include <IEvent/IEvent.h>


// gl
#include <GL/glew.h>
#include <SDL.h>

// must after gl
#include "WindowData.h"

namespace OE1Core
{
	typedef std::function<void(OECore::IEvent&)> EventCallback;
	typedef std::function<bool(const SDL_Event*)> EventPollCallback;
	typedef std::function<void(int, int)> FrameSizeUpdateCallback;
	class BaseWindow
	{
	public:
		BaseWindow(SDL_Event* _event = nullptr, const char* _name = "Win", SDL_GLContext _shared_context = nullptr, int _width = -1, int _height = -1);
		virtual ~BaseWindow();
		virtual SDL_Window* GetWin();
		WindowArg m_Args;
		inline operator bool() const { return m_Args.Running; };
		virtual void SetClearColor(float _color[4] = nullptr);
		virtual void SetClearColor(std::initializer_list<float> _list);
		virtual void Update();
		virtual void SwapBuffer();
		virtual void EnableWin();
		virtual void DisableWin();
		virtual void Close();
		virtual void PullEvent();

		virtual void RegisterFollowUpEventCallback(const EventCallback& _callback);
		virtual void RegisterEventCallback(const EventCallback& _callback);
		virtual void RegisterImGuiSDLEventProcessorCallback(const EventPollCallback& _event_pull_callback);
		virtual void RegisterFrameSizeUpdateCallback(const FrameSizeUpdateCallback& _evet_frame_size);

		virtual void OnEvent(OECore::IEvent& e) = 0;
		virtual void ResetCallbacks() = 0;
		virtual SDL_Event* GetEvent();


	protected:
		void RegisterEventCalls();
		void InitRenderState();
		void InitOpenGLContext();
		void InitWindow();

	protected:
		virtual bool HandleWindowCloseEvent(OECore::WindowCloseEvent& e) = 0;
		virtual bool HandleWindowResizeEvent(OECore::WindowResizeEvent& e) = 0;
		virtual bool HandleWindowMax(OECore::WindowMaximizedEvent& e) = 0;
		virtual bool HandleWindowMin(OECore::WindowMinimizedEvent& e) = 0;
		virtual bool HandleApplicationKeyInput(OECore::KeyPressedEvent& e) = 0;

	protected:
		Uint64 m_LastFrameTime = 0;
		Uint64 m_CurrentTime = 0;
		bool m_IsSharedContext = false;
		SDL_GLContext m_SharedContext = nullptr;
		SDL_Event* m_Event = nullptr;

	protected:
		EventPollCallback m_EventPullCallback;
		EventCallback m_Callback;
		EventCallback m_FollowUpEventCallback;
		FrameSizeUpdateCallback m_FrameSizeUpdateCallbak;

	};
}


#endif // !OE1_WINDOW_H_
