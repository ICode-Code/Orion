#ifndef OE1_MAIN_VIEWPORT_H_
#define OE1_MAIN_VIEWPORT_H_

#include "../BaseViewport.h"
#include "../Util/VPActionButton/ActionButtonTransformGroup.h"
#include "../Util/VPActionButton/ActionButtonModeGroup.h"
#include "../Util/VPActionButton/ActionButtonRenderModeGroup.h"
#include "../Util/VPActionButton/ActionButtonUtilityGroup.h"

namespace OE1Core
{
	class MainViewport : public BaseViewport
	{
	public:
		MainViewport();
		~MainViewport();


		void Update() override;
		void Render() override;

	protected:
		void HandleActionButton();
		void HandlePayloadPackage();
		void HandleClickOverViewport();
		void HandleGIZMO();


	protected:
		ImGuizmo::OPERATION m_Operation;
		ImGuizmo::MODE m_Mode;
		ActionButtonTransformGroup m_TransformGroupButton;
		ActionButtonModeGroup m_ModeGroup;
		ActionButtonRenderModeGroup m_RenderModeGroup;
		ActionButtonUtilityGroup m_UtilityGroup;
		bool m_EnableSnap = false;
		bool m_ShowActionButton = true;

	};
}

#endif // !OE1_MAIN_VIEWPORT_H_
