#include "GUIBase.h"



namespace OE1Core
{
	GUIBase::GUIBase(GLFWwindow* _window)
	{
		s_Window = _window;
		s_GUI = new OE1Core::Gui(s_Window);


		s_Layers.push_back(new ContentBrowserLayer());
		s_Layers.push_back(new InspectorLayer());
		s_Layers.push_back(new LogLayer());
		s_Layers.push_back(new SceneHierarchyLayer());
		s_Layers.push_back(new TopMenuLayer());
		s_Layers.push_back(new ProjectDirLayer());
		s_Layers.push_back(new ToolBarLayer());
		s_Layers.push_back(new ThreadInfoLayer());


		/// Mini Windows
		s_MiniWins.push_back(new CloseWin());
		s_MiniWins.push_back(new PreferenceWin());
		s_MiniWins.push_back(new Asset3DLoaderWin());
		s_MiniWins.push_back(new ProjectCreatorWin());


		/// Viewport
		s_Viewports.push_back(new MainViewport());
	}
	GUIBase::~GUIBase()
	{
		for (auto _layer : s_Layers)
			delete _layer;

		for (auto _mini : s_MiniWins)
			delete _mini;

		for (auto _viewport : s_Viewports)
			delete _viewport;

		delete s_GUI;
	}
	void GUIBase::Update()
	{
		for (size_t i = 0; i < s_Layers.size(); i++)
		{
			s_Layers[i]->Update();
			s_Layers[i]->Render();
		}

		for (size_t i = 0; i < s_MiniWins.size(); i++)
			s_MiniWins[i]->Render();

		for (size_t i = 0; i < s_Viewports.size(); i++)
			s_Viewports[i]->Render();

	}
	void GUIBase::SetContext(GLFWwindow* _window)
	{
		s_Window = _window;
	}
	void GUIBase::Attach()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
		ImGuizmo::BeginFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
	}
	void GUIBase::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(s_Window);
		}
	}
}