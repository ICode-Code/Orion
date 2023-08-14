#ifndef OE1_DISPATCHER_H_
#define OE1_DISPATCHER_H_

#include "Event.h"

namespace OE1Core
{
	class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) : m_Event(e) {  }
		template <typename T> using EventFn = std::function<bool(T&)>;

		template <typename T> bool Dispatch(EventFn<T> fun)
		{
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.mHandeld = fun(*(T*)&m_Event);
				return true;
			}
			return false;
		}

	protected:
		Event& m_Event;
	};
}


#endif // !OE1_DISPATCHER_H_
