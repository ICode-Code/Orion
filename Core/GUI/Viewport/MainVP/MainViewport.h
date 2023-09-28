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
		void OnEvent(OECore::IEvent& e) override;

	protected:
		void HandleActionButton();
		void HandlePayloadPackage();
		void HandleClickOverViewport();
		void HandleGIZMO();

	protected: // event
		bool HandleKeyRelease(OECore::KeyReleaseEvent& e);
		bool HandleKeyPress(OECore::KeyPressedEvent& e);


	protected:
		ImGuizmo::OPERATION				m_Operation;
		ImGuizmo::MODE					m_Mode;
		float							m_SnapTranslation;
		float							m_SnapRotation;
		glm::vec3						m_SnapValue;
		ActionButtonTransformGroup		m_TransformGroupButton;
		ActionButtonModeGroup			m_ModeGroup;
		ActionButtonRenderModeGroup		m_RenderModeGroup;
		ActionButtonUtilityGroup		m_UtilityGroup;
		bool							m_EnableSnap;
		bool							m_ShowActionButton;
		bool							m_MouseOverViewport;
		bool							m_IsLeftShitPressed;
		bool							m_IsCloning;

	};
}

#endif // !OE1_MAIN_VIEWPORT_H_
