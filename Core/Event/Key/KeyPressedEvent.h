#ifndef OE1_KEY_PRESSED_EVENT_H_
#define OE1_KEY_PRESSED_EVENT_H_

#include "KeyEvent.h"

namespace OE1Core
{
	class KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; };

		static EventType GetStaticType() { return EventType::KeyPressed; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "KeyPressed"; };


	private:
		int m_RepeatCount;

	};
}


#endif // !OE1_KEY_PRESSED_EVENT_H_