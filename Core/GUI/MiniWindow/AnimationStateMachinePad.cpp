#include "AnimationStateMachinePad.h"
#include "../Core/Component/AnimationComponent/AnimationComponent.h"

namespace OE1Core
{
	AnimationStateMachinePad::AnimationStateMachinePad(Component::AnimationComponent* _comp, std::string _name)
	{
		m_AnimationComponent = _comp;
		s_ShouldOpen = true;
		m_Name = ICON_FA_CODE_BRANCH"\tState Machine - [" + _name + "]";
		m_PosePreview = (ImTextureID)(uintptr_t)AssetManager::s_TextureInternalRegistry["Pose"]->GetTexture();
	}
	AnimationStateMachinePad::~AnimationStateMachinePad()
	{
		
	}

	void AnimationStateMachinePad::Update()
	{
		ImGui::SetWindowSize({ 400, 450 });
	}

	void AnimationStateMachinePad::Render()
	{
		if (!AnimationStateMachinePad::s_ShouldOpen)
			return;
		
		ImGui::PushStyleColor(ImGuiCol_WindowBg, { 0.135f, 0.135f, 0.135f, 1.0f });
		ImGui::Begin(m_Name.c_str(), &AnimationStateMachinePad::s_ShouldOpen, s_BaseWinFlag);
		Update();


		m_CellSize = m_ThumbnailSize + m_Padding;
		m_MaxPanelWidth = ImGui::GetContentRegionAvail().x;
		m_ColumnCount = (int)(m_MaxPanelWidth / m_CellSize);
		if (m_ColumnCount < 1)
			m_ColumnCount = 1;


		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 0.051f, 0.051f, 0.051f, 1.0f });
		ImGui::BeginChild("#state_iterator");


		if (ImGui::Button("Register State", { 380.0f, 25.0f }))
			ImGui::OpenPopup("anim_state_selector");

		ImGui::SetNextWindowSize(ImVec2(200.0f, 400.0f));
		if (ImGui::BeginPopup("anim_state_selector"))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, { 3, 2 });
			ImGui::PushStyleVar(ImGuiStyleVar_ButtonTextAlign, { 0.0f, 0.5f });

			for (auto iter = ANIMATION_MAP.begin(); iter != ANIMATION_MAP.end(); iter++)
			{
				std::string _name = ICON_FA_CODE_BRANCH"\t" + iter->second;
				if (ImGui::Button(_name.c_str(), { 200.0f, 25.0f }))
				{
					m_AnimationComponent->GetAnimationController()->BindVoidState(iter->first, iter->second);

					ImGui::CloseCurrentPopup();
				}
			}

			ImGui::PopStyleVar(2);

			ImGui::EndPopup();
		}


		ImGui::Columns(m_ColumnCount, "innerList", false);

		auto& anim_state_list = m_AnimationComponent->GetAnimationController()->m_BindedStateAnimationName;

		int  i = 0;
		for (auto iter = anim_state_list.begin(); iter != anim_state_list.end(); iter++, i++)
		{
			ImGui::PushID(i);
			ImVec4 _col = { 0.15f, 0.15f, 0.15f, 1.0f };

			if (!m_AnimationComponent->GetAnimationController()->ValidState(iter->second))
				_col = { 0.30f, 0.03f, 0.03f, 0.5f };
			else 
				_col = { 0.03f, 0.30f, 0.03f, 0.5f };

			PushPanalItemStyle(_col);
			ImGui::ImageButton(m_PosePreview, { m_ThumbnailSize, m_ThumbnailSize }, { 1, 0 }, { 0, 1 });
			
			if (ImGui::BeginDragDropTarget())
			{

				if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("bind_anim_payload"))
				{
					Animation* package = (Animation*)payload->Data;


					m_AnimationComponent->GetAnimationController()->BindState(
						iter->second, // state
						AssetManager::GetAnimation(package->GetName()),
						iter->first
					);
				}

				ImGui::EndDragDropTarget();
			}
			
			ImGui::SeparatorText(iter->first.c_str());
			ImGui::SameLine();
			if (ImGui::Button(ICON_FA_LINK))
			{
				if (m_AnimationComponent->GetAnimationController()->ValidState(iter->second))
				{
					m_AnimationComponent->GetAnimationController()->SetDefaultState(iter->second);
				}
			}
			PopPanalItemStyle();
			ImGui::NextColumn();

			ImGui::PopID();
		}


		ImGui::Columns(1);

		ImGui::EndChild();
		ImGui::PopStyleColor();

		ImGui::End();
		ImGui::PopStyleColor();
	}

	void AnimationStateMachinePad::PushPanalItemStyle(ImVec4 _col)
	{
		ImGui::PushStyleColor(ImGuiCol_Button, _col);
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, { 0.10f, 0.10f, 0.10f, 1.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, { 1 });
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, { 5.0f, 5.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_SeparatorTextAlign, { 0.50f, 0.0f });
		ImGui::PushStyleVar(ImGuiStyleVar_SeparatorTextPadding, { 0, 0 });
		ImGui::PushStyleVar(ImGuiStyleVar_SeparatorTextBorderSize, { 2 });

	}
	void AnimationStateMachinePad::PopPanalItemStyle()
	{
		ImGui::PopStyleVar(6);
		ImGui::PopStyleColor(2);
	}
}