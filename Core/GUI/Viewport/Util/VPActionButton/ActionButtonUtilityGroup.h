#ifndef OE1_ACTION_BUTTON_UTILITY_GROUP_H_
#define OE1_ACTION_BUTTON_UTILITY_GROUP_H_


#include "ActionButtonBase.h"
#include "../Core/CameraPackage/CameraPackage.h"


namespace OE1Core
{
	class ActionButtonUtilityGroup : public ActionButtonBase
	{
	public:
		ActionButtonUtilityGroup();
		~ActionButtonUtilityGroup();

		void Draw(bool& _show_action_button, CameraPackage& _camera);

	protected:
		std::pair<bool, VPNavButton*> m_QuickCamera;
		std::pair<bool, VPNavButton*> m_HideTool;
	};
}

#endif // !OE1_ACTION_BUTTON_UTILITY_GROUP_H_
