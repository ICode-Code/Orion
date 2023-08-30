#include "BaseViewport.h"


namespace OE1Core
{
	void BaseViewport::UpdateViewport()
	{
		m_IsMouseOverViewPort = ImGui::IsWindowHovered();
		ImVec2 current_size = ImGui::GetWindowSize();
		if ((m_ViewportSize.x == current_size.x) && m_ViewportSize.y == current_size.y)
			return;
		m_ViewportSize = current_size;
		SceneManager::GetActiveScene()->Update((int)m_ViewportSize.x, (int)m_ViewportSize.y);
	}
	void BaseViewport::MousePoseRefToViewport(ImVec2& _viewport)
	{
		ImVec2 min_bound = ImGui::GetWindowPos();
		min_bound.x += _viewport.x;
		min_bound.y += _viewport.y;

		ImVec2 max_bound{ 
			min_bound.x + m_ViewportSize.x,
			min_bound.y + m_ViewportSize.y
		};

		glm::vec2 viewport_bound[2];
		viewport_bound[0] = { min_bound.x, min_bound.y };
		viewport_bound[1] = { max_bound.x, max_bound.y };

		ImVec2 absolute_mouse_position = ImGui::GetMousePos();

		absolute_mouse_position.x -= viewport_bound[0].x;
		absolute_mouse_position.y -= viewport_bound[0].y;

		glm::vec2 viewport_size = viewport_bound[1] - viewport_bound[0];
		absolute_mouse_position.y = viewport_size.y - absolute_mouse_position.y; // Invert y Axis

		m_MousePosition.x = (int)absolute_mouse_position.x;
		m_MousePosition.y = (int)absolute_mouse_position.y;
	}
}