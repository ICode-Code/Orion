#include "PreferenceWin.h"


namespace OE1Core
{
	PreferenceWin::PreferenceWin()
	{
		
	}
	PreferenceWin::~PreferenceWin()
	{

	}

	void PreferenceWin::Update()
	{

	}
	void PreferenceWin::Render()
	{
		if (!PreferenceWin::s_ShouldOpen)
			return;

		//

		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.235f, 0.235f, 0.235f, 1.0f });
		ImGui::Begin(ICON_FA_GEAR"\tPreference",&PreferenceWin::s_ShouldOpen, s_BaseWinFlag);

		//ed::SetCurrentEditor(m_NodeEditorContext);

		//	ed::Begin("My Editor", ImVec2(0.0, 0.0f));
		//		int uniqueId = 1;
		//		// Start drawing nodes.
		//		ed::BeginNode(uniqueId++);
		//			ImGui::Text("Node A");
		//				ed::BeginPin(uniqueId++, ed::PinKind::Input);
		//				ImGui::Text("-> In");
		//				ed::EndPin();
		//			ImGui::SameLine();
		//				ed::BeginPin(uniqueId++, ed::PinKind::Output);
		//				ImGui::Text("Out ->");
		//				ed::EndPin();
		//		ed::EndNode();

		//		ed::BeginNode(uniqueId++);
		//		ImGui::Text("Node G");
		//		ed::BeginPin(uniqueId++, ed::PinKind::Input);
		//		ImGui::Text("-> In");
		//		ed::EndPin();
		//		ImGui::SameLine();
		//		ed::BeginPin(uniqueId++, ed::PinKind::Output);
		//		ImGui::Text("Out ->");
		//		ed::EndPin();
		//		ed::EndNode();
		//	ed::End();

		//ed::SetCurrentEditor(nullptr);

		ImGui::End();
		ImGui::PopStyleColor();
	}
}