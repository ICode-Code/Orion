#ifndef OE1_WINDOW_H_
#define OE1_WINDOW_H_

// orion
#include <Log.h> 
#include "../../Event/IEvent.h"


// gl
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// must after gl
#include "WindowData.h"

namespace OE1Core
{
	class Window
	{
	public:
		Window(const char* _name = "Win", int _width = 1366, int _height = 768);
		~Window();

		GLFWwindow* GetWin();
		WindowArg& GetArg();
		using EVENT_CALLBACK = std::function<void(Event&)>;
		inline operator bool() const { return m_Args.Running; };
		void SetClearColor(float _color[4] = nullptr);
		void SetClearColor(std::initializer_list<float> _list);
		void Update();
		void CleanDefaultBuffer();
		void SwapZDoubleBuffer();
		void EnableWin();
		void DisableWin();
		void Close();
		void SetEventCallback(const EVENT_CALLBACK& _callback);
		


	protected:
		void InitOpenGLContext();
		void InitWindow();
		void RegisterEventCalls();

	protected:
		WindowArg m_Args;
		EVENT_CALLBACK m_Callback;
		float m_LastFrameTime = 0.0f;
		float m_CurrentTime = 0.0;

	};
}


#endif // !OE1_WINDOW_H_
