#include "LuaSourceEditor.h"


namespace OE1Core
{
	LuaSourceEditor::LuaSourceEditor(Component::ScriptComponent* _script)
	{
		m_ScriptComponent = _script;
		m_ShouldOpen = true;

		std::copy(m_ScriptComponent->m_Source.begin(), m_ScriptComponent->m_Source.end(), &m_TextBuffer[0]);
	}
	LuaSourceEditor::~LuaSourceEditor()
	{

	}
	void LuaSourceEditor::SetPurgCallback(const PURGE_CALLBACK& _callback)
	{
		m_PurgCallback = _callback;
	}
	void LuaSourceEditor::Render()
	{
		std::string _tag = ICON_FA_CODE;
		_tag += "\t";
		_tag += m_ScriptComponent->m_Name;

		
		

		PushStyle();
		ImGui::SetNextWindowSize(ImVec2(600, 400));
		ImGui::Begin(_tag.c_str(), &m_ShouldOpen, ImGuiWindowFlags_NoCollapse);
		
		ImGui::PushStyleColor(ImGuiCol_Text, { 0.9f, 0.9f, 0.3f, 1.0f });

		
		ImGui::SetWindowFontScale(1.3f); 

		 
		ImGui::InputTextMultiline("##TextEditor", m_TextBuffer, IM_ARRAYSIZE(m_TextBuffer), ImVec2(-1.0f, 300.0f), ImGuiInputTextFlags_AllowTabInput);


		ImGui::SetWindowFontScale(1.0f);
		
		ImGui::PopStyleColor();

		if (ImGui::Button("Save/Compile", { 120.0f, 0.0f }))
		{
			std::string _buf = std::string(m_TextBuffer);
			RTSIntializer::WriteSourceToFile(m_ScriptComponent->m_SourcePath, _buf);
			m_ScriptComponent->ReCompileSource();
		} ImGui::SameLine();
		if (ImGui::Button("Dismiss", { 120.0f, 0.0f }))
		{

		}

		ImGui::End();

		PopStyle();
	}
	void LuaSourceEditor::Update()
	{

	}

	void LuaSourceEditor::PushStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 3, 7 });
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 20, 3 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);

		ImGui::PushStyleColor(ImGuiCol_FrameBgActive, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_SliderGrab, { 0.7f, 0.7f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, { 0.7f, 0.7f, 0.7f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_Header, { 0.13f, 0.13f, 0.13f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_HeaderHovered, { 0.0f, 0.439f, 0.878f, 1.0f });
		ImGui::PushStyleColor(ImGuiCol_CheckMark, { 0.8f, 0.8f, 0.8f, 1.0f });
	}
	void LuaSourceEditor::PopStyle()
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();
		ImGui::PopStyleColor();


		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
		ImGui::PopStyleVar();
	}
}