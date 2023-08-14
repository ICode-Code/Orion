#ifndef OE1_MOUSE_BUTTON_RELEASE_EVENT_H_
#define OE1_MOUSE_BUTTON_RELEASE_EVENT_H_

#include "MouseButton.h"

namespace OE1Core
{
	class MouseButtonReleaseEvent : public MouseButton
	{
	public:
		MouseButtonReleaseEvent(int button) : MouseButton(button) {  }



		static EventType GetStaticType() { return EventType::MouseButtonRelease; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "MouseButtonRelease"; };

	};
}


#endif // !OE1_MOUSE_BUTTON_RELEASE_EVENT_H_