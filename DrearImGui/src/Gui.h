#ifndef OE1_GUI_H_
#define OE1_GUI_H_

#include <SDL.h>


#include <imgui/imgui.h>
#include <imgui/imgui_internal.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/ImGuizmo.h>
#include <imgui/IconsFontAwesome6.h>


namespace OE1Core
{
	class Gui
	{
	public:
		Gui(SDL_Window* _window, SDL_GLContext* _context);
		~Gui();

		ImGuiContext* GetContext();
		void SetGLContext(const SDL_GLContext* _context);

		inline static ImVec4 s_ThemeColor = ImVec4(0.0f, 0.439f, 0.878f, 1.0f);


	protected:
		void Init(SDL_Window* _window, SDL_GLContext* _context);
		

	protected:
		void InstallDarkTheme();
	};
}

#endif // !OE1_GUI_H_
