#include "VPActionButton.h"


namespace OE1Core
{
	VPNavButton::VPNavButton(const char* _icon)
	{
		m_Icon = _icon;
	}

	bool VPNavButton::Draw()
	{
		return ImGui::Button(m_Icon);
	}
}