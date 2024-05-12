#ifndef OE1_WINDOW_MANAGER_H_
#define OE1_WINDOW_MANAGER_H_

#include "BaseWindow.h"
#include "BootWin/Engine/EngineWindow.h"
#include "BootWin/Genesis/GenesisWindow.h"
#include <unordered_map>

namespace OE1Core
{
#define ENGINE_MAIN_WINDOW "Orion64x"
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

		static EngineWindow* GetEngineWindow();
		static GenesisWindow* GetGenesisWindow();
		static GenesisWindow* IgniteGenesisWindow();
		static void DestroyGenesisWindow();
	protected:
		inline static SDL_Event s_Event;
		inline static EngineWindow* s_EngineWindow = nullptr;
		inline static GenesisWindow* s_GenesisWindow = nullptr;

	protected:
		static void InitSDL();
		static void InitGLEW();
		static void ShowSystemLog();
		
	};
}

#endif // !OE1_WINDOW_MANAGER_H_
