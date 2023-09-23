#ifndef OE1_ACTION_BUTTON_MODE_GROUP_H_
#define OE1_ACTION_BUTTON_MODE_GROUP_H_

#include "ActionButtonBase.h"

namespace OE1Core
{
	class ActionButtonModeGroup : public ActionButtonBase
	{
	public:
		ActionButtonModeGroup();
		~ActionButtonModeGroup();

		void Draw(ImGuizmo::MODE& _mode, bool& _snap);

	protected:
		void DrawButton(std::pair<ImGuizmo::MODE, VPNavButton*>& _button, ImGuizmo::MODE& _mode);
		void DrawButton(std::pair<bool, VPNavButton*>& _button, bool& _snap);


	protected:
		std::pair<ImGuizmo::MODE, VPNavButton*>  m_Mode;
		std::pair<bool, VPNavButton*> m_Snap;


	protected: // style
		float m_Size = 30.0f;
		ImVec4 m_Background{ 0.19f, 0.19f, 0.19f, 1.0f };
		float m_Rounding = 1.3f;
		float m_SpacingBetween = 1.0f;
	};
}

#endif // !OE1_ACTION_BUTTON_MODE_GROUP_H_
