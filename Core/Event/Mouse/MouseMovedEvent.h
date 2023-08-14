#ifndef OE1_MOUSE_MOVED_EVENT_H_
#define OE1_MOUSE_MOVED_EVENT_H_

#include "../Event.h"

namespace OE1Core
{
	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(double x, double y) : m_MousePosX(x), m_MousePosY(y) {   }

		inline double GetX() const { return m_MousePosX; };
		inline double GetY() const { return m_MousePosY; };

		static EventType GetStaticType() { return EventType::MouseMoved; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "MouseMoved"; };
		virtual int GetCatagoryFlags() const override { return EventCatagory::Mouse | EventCatagory::Input; }


	private:
		double m_MousePosX;
		double m_MousePosY;
	};
}


#endif // !OE1_MOUSE_MOVED_EVENT_H_