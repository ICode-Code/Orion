#ifndef OE1_ACTION_BUTTON_BASE_H_
#define OE1_ACTION_BUTTON_BASE_H_

#include "VPActionButton.h"

namespace OE1Core
{
	class ActionButtonBase
	{
	public:
		ActionButtonBase();
		~ActionButtonBase();


	protected: // style
		float m_Size = 30.0f;
		ImVec4 m_Background{ 0.19f, 0.19f, 0.19f, 1.0f };
		float m_Rounding = 1.3f;
		float m_SpacingBetween = 1.0f;

	protected:
		void OpenDefaultActionButtonStyle();
		void CloseDefaultActionButtonStyle();
	};
}

#endif // !OE1_ACTION_BUTTON_BASE_H_
