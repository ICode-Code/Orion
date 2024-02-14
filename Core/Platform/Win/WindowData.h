#ifndef OE1_WINDOW_DATA_H_
#define OE1_WINDOW_DATA_H_


#include <SDL.h>

namespace OE1Core
{
	struct WindowArg
	{
		const char* UserDataKey = "EventCallback";
		SDL_Event SDL_Event;

		SDL_GLContext MainContext;
		SDL_GLContext SharedContext;

		SDL_Window* Win;
		int Width;
		int Height;
		bool Running = false;
		bool Maximized = false;
		const char* Name;
		float DeltaTime;
		float ClearColor[4]{ 0.1f, 0.1f, 0.1f, 1.0f };
	};
}

#endif // !OE1_WINDOW_DATA_H_
