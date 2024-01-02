#include "GUIBase.h"



namespace OE1Core
{
	GUIBase::GUIBase(SDL_Window* _window, SDL_GLContext* _context)
	{
		s_GUI = new OE1Core::Gui(_window, _context);


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
		s_MiniWins.push_back(new RenameWin());
		s_MiniWins.push_back(new MinTextureFilterWin());


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

		s_Layers.clear();
		s_MiniWins.clear();
		s_Viewports.clear();
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

		auto material_view = MaterialManager::GetMaterialView();
		for (auto& view : material_view)
		{
			view.second->Update();
			view.second->Render();

			if (!view.second->IsOpen())
				MaterialManager::RemoveMaterialView(view.second->GetMaterial());
		}

		

	}
	void GUIBase::OnEvent(OECore::IEvent& e)
	{
		for (size_t i = 0; i < s_Viewports.size(); i++)
			s_Viewports[i]->OnEvent(e);
	}
	void GUIBase::Attach()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	}
	void GUIBase::Render(SDL_Window* _window, SDL_GLContext& _context)
	{
		ImGui::Render();
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			SDL_GL_MakeCurrent(_window, _context);
		}
	}
}