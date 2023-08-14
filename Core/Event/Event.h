#ifndef OE1_EVENT_H_
#define OE1_EVENT_H_


#include <string>
#include <functional>

namespace OE1Core
{
	#define BIT(x) (1 << x)
	class EventDispatcher;

	enum class EventType
	{
		None = 0,
		WindowClose,
		WindowResize,
		WindowFocus,
		WindowLostFocus,
		WindowMoved,

		KeyPressed,
		KeyReleased,
		KeyRepeat,
		KeyTyped,

		MouseButtonPressed,
		MouseButtonRelease,
		MouseMoved,
		MouseScrolled
	};


	enum EventCatagory
	{
		None = 0,
		Application = BIT(1),
		Input = BIT(2),
		Keyboard = BIT(3),
		Mouse = BIT(4),
		MouseBUtton = BIT(5),
	};
#define EVENT_CLASS_TYPE(type)  static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override {return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATAGORY(catagory) virtual int GetCatagoryFlags() const override { return catagory; }

	class Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCatagoryFlags() const = 0;

		inline bool IsInCatagory(EventCatagory catagory)
		{
			return GetCatagoryFlags() & catagory;
		}

	public:
		bool mHandeld = false;
	};
}

#endif // !OE1_EVENT_H_
