#ifndef OE1_BASE_VIEWPORT_H_
#define OE1_BASE_VIEWPORT_H_


#include "../../Platform/Win/WindowManager.h"
#include "../Native/WindowFileDialog.h"
#include "../../Core/Command/Commnad.h"
#include "../MiniWindow/IMiniWin.h"
#include "../../Common/Shared/ViewportArgs.h"
#include "../../Core/Scene/SceneManager.h"
#include <Gui.h>


namespace OE1Core
{
	class BaseViewport
	{
	public:
		virtual ~BaseViewport() = default;

		virtual void Update() = 0;
		virtual void Render() = 0;


	protected:
		// Call this inside Begin()  - End() UI call
		void UpdateViewport();
		// This will update -m_MousePosition- 
		void MousePoseRefToViewport(ImVec2& _viewport);

	protected:
		ImGuiWindowFlags m_DefaultViewportFlags =
			ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoScrollWithMouse
			| ImGuiWindowFlags_NoCollapse
			|	ImGuiWindowFlags_NoMove;
		ImVec2			m_ViewportSize{ 0.0f, 0.0f };
		ImVec2			m_Offset;
		ImVec2			m_MinBound;
		glm::ivec2		m_MousePosition;
		bool			m_IsMouseOverViewPort = false;
		bool			m_IsRightMouseButtonHeld = false;
		bool			m_IsLeftMouseButtonHeld = false;
		bool			m_IsMiddleMouseButtonHeld = false;
	};
}

#endif // !OE1_BASE_VIEWPORT_H_
