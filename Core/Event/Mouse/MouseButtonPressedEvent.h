#ifndef OE1_MOUSE_PRESSED_EVENT_H_
#define OE1_MOUSE_PRESSED_EVENT_H_


#include "MouseButton.h"

namespace OE1Core
{
	class MouseButtonPressedEvent : public MouseButton
	{
	public:
		MouseButtonPressedEvent(int button) : MouseButton(button) {  }


		static EventType GetStaticType() { return EventType::MouseButtonPressed; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "MouseButtonPressed"; };


	};
}


#endif // !OE1_MOUSE_PRESSED_EVENT_H_