#ifndef OE1_CAMERA_PACKAGE_COMPONENT_H_
#define OE1_CAMERA_PACKAGE_COMPONENT_H_

#include "../../CameraPackage/CameraPackage.h"

namespace OE1Core
{
	namespace Component
	{
		class CameraPackageComponent
		{
		public:
			CameraPackageComponent(CameraPackage* _camera, std::string _name);
			~CameraPackageComponent();

			void SetCameraPackage(CameraPackage* _camera);
			void SetCameraName(std::string _name);

			CameraPackage* GetCameraPackage();
			const char* GetCameraPackageName();

			

		private:
			const char* m_Name;
			CameraPackage* m_Camera = nullptr;
		};
	}
}

#endif // !OE1_CAMERA_PACKAGE_COMPONENT_H_
