#ifndef OE1_ACTION_BUTTON_TRANSFORM_GROUP_H_
#define OE1_ACTION_BUTTON_TRANSFORM_GROUP_H_

#include "ActionButtonBase.h"

namespace OE1Core
{
	class ActionButtonTransformGroup : public ActionButtonBase
	{
	public:
		ActionButtonTransformGroup();
		~ActionButtonTransformGroup();

		void Draw(ImGuizmo::OPERATION& _operation);

	protected:
		void DrawButton(std::pair<ImGuizmo::OPERATION, VPNavButton*>& _button, ImGuizmo::OPERATION& _operation);


	protected:
		std::pair<ImGuizmo::OPERATION, VPNavButton*>  m_Bound;
		std::pair<ImGuizmo::OPERATION, VPNavButton*> m_Translation;
		std::pair<ImGuizmo::OPERATION, VPNavButton*> m_Rotation;
		std::pair<ImGuizmo::OPERATION, VPNavButton*> m_Scale;
	};
}

#endif // !OE1_ACTION_BUTTON_TRANSFORM_GROUP_H_
