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
	class Window
	{
	public:
		Window(const char* _name = "Win", int _width = -1, int _height = -1);
		~Window();

		SDL_Window* GetWin();
		WindowArg& GetArg();
		inline operator bool() const { return m_Args.Running; };
		void SetClearColor(float _color[4] = nullptr);
		void SetClearColor(std::initializer_list<float> _list);
		void Update();
		void SwapBuffer();
		void EnableWin();
		void DisableWin();
		void Close();
		void RegisterEventCallback(const EventCallback& _callback);
		void RegisterImGuiSDLEventProcessorCallback(const EventPollCallback& _event_pull_callback);
		void PullEvent();
		


	protected:
		void InitRenderState();
		void InitOpenGLContext();
		void InitWindow();
		void RegisterEventCalls();

	protected:
		WindowArg m_Args;
		EventPollCallback m_EventPullCallback;
		EventCallback m_Callback;
		Uint64 m_LastFrameTime = 0;
		Uint64 m_CurrentTime = 0;

	};
}


#endif // !OE1_WINDOW_H_
