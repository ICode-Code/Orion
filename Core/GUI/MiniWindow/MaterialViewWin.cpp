#include "MaterialViewWin.h"


namespace OE1Core
{
	MaterialViewWin::MaterialViewWin(MasterMaterial* _material)
	{
		m_Material = _material;
		m_WinName = ICON_FA_CIRCLE_HALF_STROKE"\tMaterial: ";
		m_WinName.append(m_Material->GetName());
		m_Open = true;
		PrepareMaterialView();
	}
	MaterialViewWin::~MaterialViewWin()
	{

	}

	void MaterialViewWin::Render()
	{
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.087f, 0.087f, 0.087f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 0.0f });

		ImGui::Begin(m_WinName.c_str(), &m_Open, s_BaseWinFlag);


		ImGui::End();

		ImGui::PopStyleVar();
		ImGui::PopStyleColor();
	}
	void MaterialViewWin::Update()
	{

	}
	void MaterialViewWin::PrepareMaterialView()
	{

	}
}