#include "Gui.h"


namespace OE1Core
{
	Gui::Gui(SDL_Window* _window, SDL_GLContext* _context)
	{
		Init(_window, _context);

		s_ThemeColor = ImVec4(0.0f, 0.439f, 0.878f, 1.0f);
		//s_ThemeColor = ImVec4(0.0392157f, 0.7490196f, 0.3254902f, 1.0f);
		//s_ThemeColor = ImVec4(0.0f, 0.6235294f, 0.3019608f, 1.0f);

		InstallDarkTheme();
	}
	Gui::~Gui()
	{
		ImGui_ImplSDL2_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}


	ImGuiContext* Gui::GetContext()
	{
		return ImGui::GetCurrentContext();
	}
	void Gui::SetGLContext(const SDL_GLContext* _context)
	{

	}

	void Gui::Init(SDL_Window* _window, SDL_GLContext* _context)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();

		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

		io.Fonts->AddFontFromFileTTF("../StaticAsset/fonts/Rajdhani/Rajdhani-Bold.ttf", 13.0f);
		io.DisplaySize = ImVec2(1366.0f, 768.0f);
		
		io.UserData = _window;
		
		ImGui_ImplSDL2_InitForOpenGL(_window, _context);
		ImGui_ImplOpenGL3_Init("#version 130 core");

		static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
		ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
		io.Fonts->AddFontFromFileTTF(FONT_ICON_FILE_NAME_FAS, 12.0f, &icons_config, icons_ranges);
	}

	void Gui::InstallDarkTheme()
	{
		ImVec4* colors = ImGui::GetStyle().Colors;
		colors[ImGuiCol_Text]						= ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
		colors[ImGuiCol_TextDisabled]				= ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
		colors[ImGuiCol_WindowBg]					= ImVec4(0.051f, 0.051f, 0.051f, 1.000f);
		colors[ImGuiCol_ChildBg]					= ImVec4(0.101f, 0.101f, 0.101f, 1.000f);
		colors[ImGuiCol_PopupBg]					= ImVec4(0.20f, 0.20f, 0.20f, 1.0f);

		colors[ImGuiCol_Border]						= ImVec4(0.235f, 0.235f, 0.235f, 0.110f);
		colors[ImGuiCol_BorderShadow]				= ImVec4(0.304f, 0.304f, 0.304f, 1.0f);
		//0.141
		colors[ImGuiCol_FrameBg]					= ImVec4(0.141f, 0.141f, 0.141f, 0.54f);
		colors[ImGuiCol_FrameBgHovered]				= ImVec4(0.19f, 0.19f, 0.19f, 1.0f);
		colors[ImGuiCol_FrameBgActive]				= ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_TitleBg]					= ImVec4(0.235f, 0.235f, 0.235f, 1.000f);
		colors[ImGuiCol_TitleBgActive]				= ImVec4(0.235f, 0.235f, 0.235f, 1.00f);
		colors[ImGuiCol_TitleBgCollapsed]			= ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
		colors[ImGuiCol_MenuBarBg]					= ImVec4(0.235f, 0.235f, 0.235f, 1.000f);
		colors[ImGuiCol_ScrollbarBg]				= ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ScrollbarGrab]				= ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabHovered]		= ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
		colors[ImGuiCol_ScrollbarGrabActive]		= ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_CheckMark]					= s_ThemeColor;
		colors[ImGuiCol_SliderGrab]					= ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
		colors[ImGuiCol_SliderGrabActive]			= ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
		colors[ImGuiCol_Button]						= ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
		colors[ImGuiCol_ButtonHovered]				= s_ThemeColor; 
		colors[ImGuiCol_ButtonActive]				= ImVec4(0.17f, 0.17f, 0.17f, 1.0f);
		colors[ImGuiCol_Header]						= ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_HeaderHovered]				= ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
		colors[ImGuiCol_HeaderActive]				= ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
		colors[ImGuiCol_Separator]					= ImVec4(0.493f, 0.493f, 0.493f, 0.290f);
		colors[ImGuiCol_SeparatorHovered]			= ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_SeparatorActive]			= ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_ResizeGrip]					= ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_ResizeGripHovered]			= ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
		colors[ImGuiCol_ResizeGripActive]			= ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
		colors[ImGuiCol_Tab]						= ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabHovered]					= ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
		colors[ImGuiCol_TabActive]					= ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
		colors[ImGuiCol_TabUnfocused]				= ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TabUnfocusedActive]			= ImVec4(0.249f, 0.235f, 0.235f, 1.000f);
		colors[ImGuiCol_DockingPreview]				= ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_DockingEmptyBg]				= ImVec4(0.00f, 0.00f, 0.00f, 0.1f); // back
		colors[ImGuiCol_PlotLines]					= ImVec4(0.015f, 0.806f, 0.620f, 1.000f); // The Green One
		colors[ImGuiCol_PlotLinesHovered]			= ImVec4(0.015f, 0.806f, 0.620f, 1.000f);
		colors[ImGuiCol_PlotHistogram]				= ImVec4(0.015f, 0.806f, 0.620f, 1.000f);
		colors[ImGuiCol_PlotHistogramHovered]		= ImVec4(0.015f, 0.806f, 0.620f, 1.000f);
		colors[ImGuiCol_TableHeaderBg]				= ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderStrong]			= ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
		colors[ImGuiCol_TableBorderLight]			= ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
		colors[ImGuiCol_TableRowBg]					= ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
		colors[ImGuiCol_TableRowBgAlt]				= ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
		colors[ImGuiCol_TextSelectedBg]				= ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
		colors[ImGuiCol_DragDropTarget]				= ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
		colors[ImGuiCol_NavHighlight]				= ImVec4(0.015f, 0.806f, 0.620f, 1.00f);
		colors[ImGuiCol_NavWindowingHighlight]		= ImVec4(0.015f, 0.806f, 0.620f, 0.70f);
		colors[ImGuiCol_NavWindowingDimBg]			= ImVec4(0.015f, 0.806f, 0.620f, 0.20f);
		colors[ImGuiCol_ModalWindowDimBg]			= ImVec4(0.2f, 0.2f, 0.2f, 0.4f);

		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowPadding				= ImVec2(8.00f, 11.00f);
		style.FramePadding				= ImVec2(6.00f, 5.00f);
		style.CellPadding				= ImVec2(6.00f, 6.00f);
		style.ItemSpacing				= ImVec2(20.0f, 13.00f);
		style.ItemInnerSpacing			= ImVec2(6.00f, 6.00f);
		style.TouchExtraPadding			= ImVec2(0.00f, 0.00f);
		style.IndentSpacing = 0;
		style.ScrollbarSize = 15;
		style.GrabMinSize = 6;
		style.WindowBorderSize = 1;
		style.ChildBorderSize = 1;
		style.PopupBorderSize = 1;
		style.FrameBorderSize = 1;
		style.TabBorderSize = 0.3f;
		style.WindowRounding = 0;
		style.ChildRounding = 0;
		style.FrameRounding = 0;
		style.PopupRounding = 2;
		style.ScrollbarRounding = 9;
		style.GrabRounding = 0;
		style.LogSliderDeadzone = 4;
		style.TabRounding = 0;
		style.WindowMenuButtonPosition = ImGuiDir_Left;
		style.FrameBorderSize = 0.1f;
	}
}