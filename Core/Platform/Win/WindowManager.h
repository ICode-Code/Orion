#ifndef OE1_WINDOW_MANAGER_H_
#define OE1_WINDOW_MANAGER_H_

#include "Window.h"
#include <unordered_map>

namespace OE1Core
{
#define ENGINE_MAIN_WINDOW "Orion64x"
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		static Window*	GetWindow(std::string _name);
		static void		PurgWindow(std::string _name);
		static Window*	RegisterWindow(std::string _name, int _width = -1, int _height = -1);
	protected:
		inline static std::unordered_map<std::string, Window*> s_Windows;

	protected:
		static void InitSDL();
		static void InitGLEW();
		static void ShowSystemLog();

	protected:
		inline static bool s_HasValidContext = false;
	};
}

#endif // !OE1_WINDOW_MANAGER_H_
