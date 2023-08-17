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
	}
	GUIBase::~GUIBase()
	{
		for (auto _layer : s_Layers)
			delete _layer;
	}
	void GUIBase::Update()
	{
		for (size_t i = 0; i < s_Layers.size(); i++)
		{
			s_Layers[i]->Update();
			s_Layers[i]->Render();
		}
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