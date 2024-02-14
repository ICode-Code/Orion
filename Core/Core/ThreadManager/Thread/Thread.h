#ifndef OE1_THREAD_H_
#define OE1_THREAD_H_

#include "../PDThreadType.h"
#include <thread>
#include <SDL.h>
#include <functional>

using namespace std::chrono_literals;

namespace OE1Core
{
	class Thread
	{
	public:
		Thread(SDL_GLContext* _context = nullptr, bool _sleep_after_task = false);
		~Thread();

		void SetContext(SDL_GLContext* _context);
		void ReleaseContext();

		bool IsRunning();
		bool HasContext();

		void Task(std::function<void()>* _task);


		std::thread& GetThread();

	private:
		std::thread m_Thread;
		bool m_Running = false;
		bool m_HasContext = false;
		std::function<void()> m_Task;
		SDL_GLContext* m_Context = nullptr;
		bool m_SleepAfterTask = false;
		std::chrono::duration<double> m_SleepFor = 1.0s;


	};
}

#endif // !OE1_THREAD_H_
