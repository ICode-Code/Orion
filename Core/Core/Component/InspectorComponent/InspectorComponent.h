#ifndef OE1_INSPECTOR_COMPONENT_H_
#define OE1_INSPECTOR_COMPONENT_H_

#include <Gui.h>
#include "../../GUI/CustomFrame/CustomFrame.h"
#include "../../AssetManager/AssetManager.h"

namespace OE1Core
{
	namespace Component
	{
		class InspectorComponent
		{
		public:
			InspectorComponent() = default;
			~InspectorComponent() = default;
			void Inspect();

			void SetCameraPackageComponent(class CameraPackageComponent* _camera_package_component);
			void SetTagComponent(class TagComponent* _tag_component);
			void SetTransformComponent(class TransformComponent* _transform);
			void SetMeshComponent(class MeshComponent* _mesh);
			void SetCameraControllerComponent(class BaseCameraControllerComponent* _camera_controller);
			void SetCameraComponent(class CameraComponent* _camera_component);
			void SetSkinnedMeshComponent(class SkinnedMeshComponent* _skinned_mesh_component);
		protected: // components
			class TagComponent* m_TagComponent = nullptr;
			class TransformComponent* m_TransformComponent = nullptr;
			class MeshComponent* m_MeshComponent = nullptr;
			class BaseCameraControllerComponent* m_BaseCameraControllerComponent = nullptr;
			class CameraComponent* m_CameraComponent = nullptr;
			class CameraPackageComponent* m_CameraPackageComponent = nullptr;
			class SkinnedMeshComponent* m_SkinnedMeshComponent = nullptr;

		protected: // flag
			ImGuiTreeNodeFlags m_TreeNodeFlags = ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_Selected | ImGuiTreeNodeFlags_FramePadding;

		protected: // functions
			void ITag();
			void ITransform();
			void IMesh();
			void ICamController();
			void ICamera();
			void ICameraPackage();
			void ISkinnedMesh();

		};
	}
}

#endif // !OE1_INSPECTOR_COMPONENT_H_
