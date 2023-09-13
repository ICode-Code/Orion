#ifndef OE1_WINDOW_FILE_DIALOG_H_
#define OE1_WINDOW_FILE_DIALOG_H_

#include <SDL.h>
#include <SDL_syswm.h>

#include <Windows.h>

#include <commdlg.h> 

#include <string>

namespace OE1Core
{
	class WindowFileDialog
	{
	public:
		static std::string LoadFile(const char* _filter, SDL_Window* _window, const char* _title = "Load Asset");
	};
}


#endif // !OE1_WINDOW_FILE_DIALOG_H_
