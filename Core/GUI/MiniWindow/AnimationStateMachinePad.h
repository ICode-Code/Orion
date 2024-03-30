#ifndef OE1_ANIMATION_STATE_MACHINE_PAD_H_
#define OE1_ANIMATION_STATE_MACHINE_PAD_H_



#include "BaseMiniWindw.h"


namespace OE1Core
{
	class AnimationStateMachinePad : public BaseMiniWindow
	{
	public:
		AnimationStateMachinePad(class Component::AnimationComponent* _comp, std::string _name);
		~AnimationStateMachinePad();

		virtual void Render() override;
		inline static bool s_ShouldOpen = false;

	private:
		virtual void Update() override;
		Component::AnimationComponent* m_AnimationComponent = nullptr;
		std::string m_Name = "%%";

	private:
		float m_Padding = 45.0f;
		float m_ThumbnailSize = 65.0f;
		float m_CellSize = m_ThumbnailSize + m_Padding;
		float m_MaxPanelWidth;
		int m_ColumnCount;
		ImTextureID m_PosePreview;

	private: // Util func
		void PushPanalItemStyle(ImVec4 _col = { 0.15f, 0.15f, 0.15f, 1.0f });
		void PopPanalItemStyle();
	};
}


#endif // !OE1_ANIMATION_STATE_MACHINE_PAD_H_
