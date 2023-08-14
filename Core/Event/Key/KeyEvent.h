#ifndef OE1_KEY_EVENT_H_
#define OE1_KEY_EVENT_H_

#include "../Event.h"

namespace OE1Core
{
	class KeyEvent : public Event
	{
	protected:
		KeyEvent(int keycode) : m_KeyCode(keycode) {};

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		virtual int GetCatagoryFlags() const override { return EventCatagory::Keyboard | EventCatagory::Input; }


	private:
		int m_KeyCode;

		
	};
}


#endif // !OE1_KEY_EVENT_H_