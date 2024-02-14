#include "ThreadManager.h"


namespace OE1Core
{
	ThreadManager::ThreadManager(SDL_GLContext* _context)
	{
		s_PDThreadPool.insert(std::make_pair(PD_THREAD::RENDERER, new Thread(_context)));
	}
	ThreadManager::~ThreadManager()
	{

	}
	Thread* ThreadManager::GetThread(PD_THREAD _type)
	{
		return s_PDThreadPool[_type];
	}
	Thread* ThreadManager::GetThread(std::string _name)
	{
		if (s_DynamicThreadPool.find(_name) == s_DynamicThreadPool.end())
			return nullptr;
		return s_DynamicThreadPool[_name];
	}
	Thread* ThreadManager::RegisterThread(std::string _name)
	{
		if (s_DynamicThreadPool.find(_name) != s_DynamicThreadPool.end())
			return nullptr;

		s_DynamicThreadPool.insert(std::make_pair(_name, new Thread()));

		return s_DynamicThreadPool[_name];
	}
}