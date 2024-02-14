#ifndef OE1_THREAD_MANAGER_H_
#define OE1_THREAD_MANAGER_H_

#include "Thread/Thread.h"
#include <unordered_map>

namespace OE1Core
{
	class ThreadManager
	{
	public:
		ThreadManager(SDL_GLContext* _context);
		~ThreadManager();

		static Thread* RegisterThread(std::string _name);
		static Thread* GetThread(std::string _name);

		static Thread* GetThread(PD_THREAD _type);

	private:
		inline static std::unordered_map<std::string, Thread*> s_DynamicThreadPool;
		inline static std::unordered_map<PD_THREAD, Thread*> s_PDThreadPool;
	};
}

#endif // !OE1_THREAD_MANAGER_H_
