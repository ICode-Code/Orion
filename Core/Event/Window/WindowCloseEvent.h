#ifndef OE1_WINDOW_CLOSE_EVENT_H_
#define OE1_WINDOW_CLOSE_EVENT_H_

#include "../Event.h"

namespace OE1Core
{
	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {};

		static EventType GetStaticType() { return EventType::WindowClose; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "WindowClose"; };
		virtual int GetCatagoryFlags() const override { return EventCatagory::Application; }

	};
}
#endif // !OE1_WINDOW_CLOSE_EVENT_H_
