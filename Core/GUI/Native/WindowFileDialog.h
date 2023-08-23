#ifndef OE1_WINDOW_FILE_DIALOG_H_
#define OE1_WINDOW_FILE_DIALOG_H_


#define GLFW_EXPOSE_NATIVE_WIN32

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <Windows.h>

#include <commdlg.h> 

#include <string>

namespace OE1Core
{
	class WindowFileDialog
	{
	public:
		static std::string LoadFile(const char* _filter, GLFWwindow* _window, const char* _title = "Load Asset");
	};
}


#endif // !OE1_WINDOW_FILE_DIALOG_H_
