#ifndef OE1_CAMERA_COMPONENT_H_
#define OE1_CAMERA_COMPONENT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

namespace OE1Core
{
	namespace Component
	{
		class CameraComponent
		{
			friend class InspectorComponent;
			friend class CameraPackageComponent;
			friend class FreeLookCameraControllerComponent;
			friend class ThirdPersonCameraControllerComponent;
			friend class BaseCameraControllerComponent;
			friend class ThirdPersonCharacterControllerComponent;
		public:
			CameraComponent();
			~CameraComponent();

			bool ShouldCull();
			glm::vec3 GetPosition() const;
			void SetResolution(glm::vec2 _res);
			void Update(glm::vec3 _position);
			void Update(glm::vec3 _position, glm::vec3 _target_position);
			void SetPitch(float _pitch);
			void SetYaw(float _yaw);
			float GetAspectRatio();
			glm::vec2 GetResolution();

			float GetPitch() const;
			float GetYaw() const;

			/// <summary>
			/// The color applied to the remaining screen after all elements in view have been drawn and there is no skybox
			/// </summary>
			glm::vec3 m_Background = glm::vec3((107.0f / 255.0f), (203.0f / 255.0f), (119.0f / 255.0f));

			float m_FrontFoliageCullDistance = 100.0f;
			int m_FieldOfView = 60;
			float m_Near = 0.3f;
			float m_Far = 1000.0f;
			float m_Exposure = 1.0f;
			int m_MSAA = 2;
			// Allow
			bool m_EnableHDR = true;
			bool m_EnableMSAA = false;

			glm::mat4 m_View = glm::mat4(1.0f);
			glm::mat4 m_Projection = glm::mat4(1.0f);

		private:
			glm::vec3 m_Front;
			glm::vec3 m_Up;
			glm::vec3 m_Right;
			const glm::vec3 m_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

			float m_Yaw;
			float m_Pitch;
			float m_AspectRatio;
			glm::vec3 m_Position;
			glm::vec2 m_Resolution;
			bool m_Active = false;
			bool m_Cull = false;
			std::vector<glm::vec3> m_FrustumCorner;
		};
	}
}

#endif // !OE1_CAMERA_COMPONENT_H_
