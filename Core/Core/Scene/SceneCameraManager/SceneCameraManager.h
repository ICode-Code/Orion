#ifndef OE1_SCENE_CAMERA_MANAGER_H_
#define OE1_SCENE_CAMERA_MANAGER_H_


#include "../Core/Component/CameraComponent/CameraComponent.h"
#include "../Core/Component/CameraControllerComponent/BaseCameraControllerComponent.h"
#include "../Core/Component/CameraControllerComponent/FreeLookCameraControllerComponent/FreeLookCameraControllerComponent.h"
#include "../Core/Component/CameraControllerComponent/ThirdPersonCameraControllerComponent/ThirdPersonCameraControllerComponent.h"

#include <map>
#include "../Core/UUID/UUID.h"


namespace OE1Core
{
	struct MasterSceneEditorCamera
	{
		MasterSceneEditorCamera(SDL_Window* _context)
		{
			Camera = new Component::CameraComponent();
			Controller = new Component::FreeLookCameraControllerComponent(_context);
			Controller->SetCameraComponent(Camera);

			Camera->SetControllerType(CameraParameter::CAMERA_CONTROLLER_TYPE::FREE_LOOK);
			Camera->SetPowerState(CameraParameter::CAMERA_POWER_STATE::ON);
			Camera->SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE::PILOT);
			Camera->SetTaskType(CameraParameter::CAMERA_TASK_TYPE::EDITOR);
		}
		~MasterSceneEditorCamera()
		{
			delete Camera;
			delete Controller;
		}
		Component::CameraComponent* Camera = nullptr;
		Component::FreeLookCameraControllerComponent* Controller = nullptr;
		UUID ID;
	};
	class SceneCameraManager
	{
	public:
		// Initialization of Camera named "MasterCamera" is guaranteed
		SceneCameraManager(SDL_Window* _window);
		~SceneCameraManager();

		/// <summary>
		/// Unleass the camera registed here it will not get buffer id
		/// </summary>
		/// <param name="_name">name of the camera</param>
		/// <param name="_camera"></param>
		/// <returns></returns>
		static Component::CameraComponent* RegisterCamera(uint64_t _uid, Component::CameraComponent* _camera);
		
		static MasterSceneEditorCamera* GetMasterCamera();
		static Component::CameraComponent* GetCamera(uint64_t _uid);
		static bool PurgeCamera(uint64_t _uid);
		static void EngagePilotMode(uint64_t _uid);
		static SDL_Window* GetContextWindow();

		static bool HasCamera(uint64_t _uid);
		static std::map<uint64_t, Component::CameraComponent*>& GetCameraList();
		
	private:
		inline static MasterSceneEditorCamera* s_MasterSceneEditorCamera = nullptr;
		inline static std::map<uint64_t, Component::CameraComponent*> s_CameraCollection;
		inline static SDL_Window* s_Context = nullptr;
	};
}

#endif // !OE1_SCENE_CAMERA_MANAGER_H_
