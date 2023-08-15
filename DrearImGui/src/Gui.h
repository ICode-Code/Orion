#ifndef OE1_GUI_H_
#define OE1_GUI_H_

#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/ImGuizmo.h>
#include <imgui/IconsFontAwesome6.h>

#include <GLFW/glfw3.h>

namespace OE1Core
{
	class Gui
	{
	public:
		Gui(GLFWwindow* _window);
		~Gui();

		ImGuiContext* GetContext();

		inline static ImVec4 s_ThemeColor = ImVec4(0.0f, 0.439f, 0.878f, 1.0f);


	protected:
		void Init(GLFWwindow* _window);
		

	protected:
		void InstallDarkTheme();
	};
}

#endif // !OE1_GUI_H_
