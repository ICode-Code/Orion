#include "CameraPackageComponent.h"


namespace OE1Core
{
	namespace Component
	{
		CameraPackageComponent::CameraPackageComponent(CameraPackage* _camera, std::string _name)
		{
			m_Name = _name.c_str();
			m_Camera = _camera;
		}
		CameraPackageComponent::~CameraPackageComponent()
		{

		}

		void CameraPackageComponent::SetCameraPackage(CameraPackage* _camera)
		{
			if (!_camera)
				return;

			m_Camera = _camera;
		}
		void CameraPackageComponent::SetCameraName(std::string _name)
		{
			if (_name.empty())
				return;
			m_Name = _name.c_str();
		}

		CameraPackage* CameraPackageComponent::GetCameraPackage()
		{
			return m_Camera;
		}
		const char* CameraPackageComponent::GetCameraPackageName()
		{
			return m_Name;
		}
	}
}