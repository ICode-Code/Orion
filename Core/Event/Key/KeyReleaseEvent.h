#ifndef OE1_KEY_RELEASE_EVENT_H_
#define OE1_KEY_RELEASE_EVENT_H_


#include "KeyEvent.h"

namespace OE1Core
{
	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keycode) : KeyEvent(keycode) {  };



		static EventType GetStaticType() { return EventType::KeyReleased; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "KeyReleased"; };

	};
}


#endif // !OE1_KEY_RELEASE_EVENT_H_