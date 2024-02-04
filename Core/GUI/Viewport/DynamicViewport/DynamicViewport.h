#ifndef OE1_VIEWPORT_CAMERA_VIEW_H_
#define OE1_VIEWPORT_CAMERA_VIEW_H_


#include "../BaseViewport.h"
#include "../Util/VPActionButton/ActionButtonBase.h"

namespace OE1Core
{
	class DynamicViewport : public BaseViewport
	{
	public:
		DynamicViewport(CameraPackage* _camera, std::string _name);
		~DynamicViewport();

		void Update() override;
		void Render() override;
		void OnEvent(OECore::IEvent& e) override;
		bool IsOpen();
		void Open();
		void Close();


	protected:
		void UpdateViewport() override;
		void ShowMinActionButton();
	protected:
		CameraPackage* m_ViewPoint = nullptr;
		ImGuiWindowFlags m_LocalViewportFlags =
			ImGuiWindowFlags_NoScrollbar
			| ImGuiWindowFlags_NoScrollWithMouse
			| ImGuiWindowFlags_NoCollapse;

	private:
		bool m_Open = false;
		CameraPackage* m_Camera = nullptr;
		std::string m_Name = "";
		ActionButtonBase m_ActionButton;
	};
}

#endif // !OE1_VIEWPORT_CAMERA_VIEW_H_
