#include "WindowFileDialog.h"


namespace OE1Core
{
	std::string WindowFileDialog::LoadFile(const char* _filter, GLFWwindow* _window)
	{
        OPENFILENAMEA oft;
        CHAR scFile[260] = { 0 };
        ZeroMemory(&oft, sizeof(OPENFILENAME));
        oft.lStructSize = sizeof(OPENFILENAME);
        oft.hwndOwner = glfwGetWin32Window(_window);
        oft.lpstrFile = scFile;
        oft.nMaxFile = sizeof(scFile);
        oft.lpstrFilter = _filter;
        oft.nFilterIndex = 1;
        oft.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (GetOpenFileNameA(&oft) == TRUE)
            return oft.lpstrFile;

        return std::string();
	}
}