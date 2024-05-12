#ifndef OE1_CAMERA_COMPONENT_H_
#define OE1_CAMERA_COMPONENT_H_

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include "../Core/DS/OptStructure/Frustum/Frustum.h"
#include "../../InfiniteVision/DisplayCanavs/IVForwardMainPassFramebuffer.h"
#include "CameraParameter.h"
#include <UniformBuffer/UniformBlockManager.h>

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

			int GetBuffertOffset();

			glm::vec3 GetPosition() const;
			glm::ivec2 GetResolution();

			void SetController(BaseCameraControllerComponent* _camera_controller);
			/// <summary>
			/// Base Controller
			/// </summary>
			/// <returns></returns>
			BaseCameraControllerComponent* GetController();

			void SetPitch(float _pitch);
			void SetYaw(float _yaw);
			bool ShouldCull();
			float GetAspectRatio();


			//////////////// UPDATE
			void Update(glm::vec3 _position);
			void Update(glm::vec3 _position, glm::vec3 _target_position);
			void UpdateRenderFrameSize(int _width, int _height);
			void UpdateBuffer(float _dt);

			GLuint GetRenderedScene();
			Renderer::IVForwardMainPassFramebuffer* MainFB();

			std::vector<glm::vec3>& GetFrustumCorner();
			Frustum& GetFrustum();

			float GetPitch() const;
			float GetYaw() const;
			void SetBufferOffset(int _offset);

			CameraParameter::CAMERA_CONTROLLER_TYPE GetControllerType();
			CameraParameter::CAMERA_FLIGHT_STATE GetFlightState();
			CameraParameter::CAMERA_POWER_STATE GetPowerState();;
			CameraParameter::CAMERA_TASK_TYPE GetTaskType();

			void SetControllerType(CameraParameter::CAMERA_CONTROLLER_TYPE _val);
			void SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE _val);
			void SetPowerState(CameraParameter::CAMERA_POWER_STATE _val);;
			void SetTaskType(CameraParameter::CAMERA_TASK_TYPE _val);

			uint64_t GetID();
			void SetID(uint64_t _val);
			void SetParentID(uint32_t _val);
			void NullifyParentID();
			uint32_t GetParentID();
			bool HasParent();

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
			glm::ivec2 m_Resolution;
			bool m_Active = false;
			bool m_Cull = false;
			std::vector<glm::vec3> m_FrustumCorner;
			Frustum m_Frustum;
			int m_BufferOffset;
			Renderer::IVForwardMainPassFramebuffer* m_MainPassFramebuffer = nullptr;

		private:
			Memory::SceneTransfrom m_BufferTransform;
			CameraParameter::CAMERA_CONTROLLER_TYPE m_ControllerType;
			CameraParameter::CAMERA_FLIGHT_STATE m_FlightState;
			CameraParameter::CAMERA_POWER_STATE m_PowerState;
			CameraParameter::CAMERA_TASK_TYPE m_TaskType;
			BaseCameraControllerComponent* m_BaseController = nullptr;


			uint64_t m_UUID;
			uint32_t m_ParentID = 0;
			bool m_HasParentEntity = false;
		};
	}
}

#endif // !OE1_CAMERA_COMPONENT_H_
