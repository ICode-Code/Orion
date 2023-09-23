#include "ActionButtonBase.h"


namespace OE1Core
{
	ActionButtonBase::ActionButtonBase()
	{

	}
	ActionButtonBase::~ActionButtonBase()
	{

	}

	void ActionButtonBase::OpenDefaultActionButtonStyle()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { m_SpacingBetween, 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, m_Rounding);
		ImGui::PushStyleColor(ImGuiCol_Button, m_Background);
	}
	void ActionButtonBase::CloseDefaultActionButtonStyle()
	{
		ImGui::PopStyleColor();
		ImGui::PopStyleVar(3);
	}
}