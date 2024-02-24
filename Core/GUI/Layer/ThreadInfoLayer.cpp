#include "ThreadInfoLayer.h"


namespace OE1Core
{
	ThreadInfoLayer::ThreadInfoLayer()
	{
		Command::RegisterThreadInfoLayerNotifyCallback(
			[this](bool _load)
			{
				this->IsLoading(_load);
			}
		);
	}
	ThreadInfoLayer::~ThreadInfoLayer()
	{

	}

	void ThreadInfoLayer::Update()
	{

	}
	void ThreadInfoLayer::IsLoading(bool _loading)
	{
		m_LoadingInProgress = _loading;
	}
	void ThreadInfoLayer::Render()
	{
		if (!m_LoadingInProgress)
			return;
		ImGui::Begin("#thread_info", NULL, ImGuiWindowFlags_NoScrollbar);

		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 2 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0 });
		ImGui::PushStyleColor(ImGuiCol_PlotHistogram, { 0.0f, 0.439f, 0.878f, 1.0f });

		ImGui::ProgressBar(Loader::CoreGeometryLoader::PROGRESS_LEVEL, { 0.0f, 0.0f });
		ImGui::SameLine();
		ImGui::TextWrapped(Loader::CoreGeometryLoader::PROGRESS_INFO.c_str());

		ImGui::PopStyleColor();
		ImGui::PopStyleVar(3);

		ImGui::End();
	}
}