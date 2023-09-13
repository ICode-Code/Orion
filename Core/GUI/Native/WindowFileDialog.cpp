#include "WindowFileDialog.h"


namespace OE1Core
{
	std::string WindowFileDialog::LoadFile(const char* _filter, SDL_Window* _window, const char* _title)
	{

        OPENFILENAMEA oft;
        CHAR scFile[260] = { 0 };
        ZeroMemory(&oft, sizeof(OPENFILENAME));
        oft.lStructSize = sizeof(OPENFILENAME);

        SDL_SysWMinfo wminfo;
        SDL_VERSION(&wminfo.version);
        void* native_window_handle = nullptr;

        if (SDL_GetWindowWMInfo(_window, &wminfo))
            native_window_handle = wminfo.info.win.window;

        if (native_window_handle == nullptr)
        {
            printf("Something want wrong! unable to open load window!");
            return std::string();
        }


        oft.hwndOwner = static_cast<HWND>(native_window_handle);
        oft.lpstrFile = scFile;
        oft.lpstrTitle = _title;
        oft.nMaxFile = sizeof(scFile);
        oft.lpstrFilter = _filter;
        oft.nFilterIndex = 1;
        oft.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&oft) == TRUE)
            return oft.lpstrFile;

        return std::string();
	}
}