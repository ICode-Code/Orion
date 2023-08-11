#ifndef OE1_WINDOW_MANAGER_H_
#define OE1_WINDOW_MANAGER_H_

#include "Window.h"
#include <unordered_map>

namespace OE1Core
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		static Window*	GetWindow(std::string _name);
		static void		PurgWindow(std::string _name);
		static Window*	RegisterWindow(std::string _name, int _width = 800, int _height = 600);
	protected:
		inline static std::unordered_map<std::string, Window*> s_Windows;

	protected:
		static void InitGLFW();
		static void InitGLEW();
		static void ShowSystemLog();

	protected:
		inline static bool s_HasValidContext = false;
	};
}

#endif // !OE1_WINDOW_MANAGER_H_
