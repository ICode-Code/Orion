#ifndef OE1_MOUSE_BUTTON_H_
#define OE1_MOUSE_BUTTON_H_

#include "../Event.h"

namespace OE1Core
{
	class MouseButton : public Event
	{
	public:
		MouseButton(int button) : m_Button(button) {  };

		inline int GetButton() const { return m_Button; };
		

		virtual int GetCatagoryFlags() const override { return EventCatagory::Mouse | EventCatagory::Input; }

	private:
		int m_Button;
	};
}


#endif // !OE1_MOUSE_BUTTON_H_