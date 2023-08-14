#ifndef OE1_KEY_REPEAT_EVENT_H_
#define OE1_KEY_REPEAT_EVENT_H_


#include "KeyEvent.h"

namespace OE1Core
{
	class KeyRepeatEvent : public KeyEvent
	{
	public:
		KeyRepeatEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) { }

		inline int GetRepeatCount() const { return m_RepeatCount; };

		static EventType GetStaticType() { return EventType::KeyRepeat; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "KeyRepeat"; };
		virtual int GetRepeatCount() { return m_RepeatCount; }

	private:
		int m_RepeatCount;
	};
}

#endif // !OE1_KEY_REPEAT_EVENT_H_
