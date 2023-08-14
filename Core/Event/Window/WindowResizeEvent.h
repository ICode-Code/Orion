#ifndef OE1_WINDOW_RESIZE_EVENT_H_
#define OE1_WINDOW_RESIZE_EVENT_H_



#include "../Event.h"

namespace OE1Core
{

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(int x, int y) : m_Width(x), m_Height(y) {  }  

		inline int GetWidth() const { return m_Width; }
		inline int GetHeight() const { return m_Height; }


		static EventType GetStaticType() { return EventType::WindowResize; };
		virtual EventType GetEventType() const override { return GetStaticType(); };
		virtual const char* GetName() const override { return "WindowResize"; };
		virtual int GetCatagoryFlags() const override { return EventCatagory::Application; }



	private:
		int m_Width;
		int m_Height;
	};
 }

#endif // !OE1_WINDOW_RESIZE_EVENT_H_