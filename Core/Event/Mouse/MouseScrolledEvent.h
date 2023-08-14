#ifndef OE1_MOUSE_SCROLLED_EVENT_H_
#define OE1_MOUSE_SCROLLED_EVENT_H_

#include "../Event.h"

namespace OE1Core
{
	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yoffset) : m_OffsetX(xOffset), m_OffsetY(yoffset) {   };

		inline float GetOffsetX() const { return m_OffsetX; };
		inline float GetOffsetY() const { return m_OffsetY;  };

		static EventType GetStaticType() { return EventType::MouseScrolled; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "MouseScrolled"; };
		virtual int GetCatagoryFlags() const override { return EventCatagory::Mouse | EventCatagory::Input; }

	private:
		float m_OffsetX;
		float m_OffsetY;
	};
}


#endif // !OE1_MOUSE_SCROLLED_EVENT_H_