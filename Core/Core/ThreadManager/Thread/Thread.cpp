#include "Thread.h"


namespace OE1Core
{
	Thread::Thread(SDL_GLContext* _context, bool _sleep_after_task)
	{
		if (_context)
			SetContext(_context);
	}
	Thread::~Thread()
	{
		ReleaseContext();
	}

	void Thread::SetContext(SDL_GLContext* _context)
	{
		SDL_GL_MakeCurrent(NULL, _context);
	}
	void Thread::ReleaseContext()
	{
		SDL_GL_MakeCurrent(NULL, NULL);
	}

	bool Thread::IsRunning()
	{
		return m_Running;
	}
	bool Thread::HasContext()
	{
		return m_HasContext;
	}


	std::thread& Thread::GetThread()
	{
		return m_Thread;
	}

	void Thread::Task(std::function<void()>* _task)
	{
		m_Thread = std::thread([=]() {
			while (m_Context)
			{
				_task;
			}
			});

	}
}