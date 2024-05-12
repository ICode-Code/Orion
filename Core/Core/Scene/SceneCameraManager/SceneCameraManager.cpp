#include "SceneCameraManager.h"


namespace OE1Core
{
	SceneCameraManager::SceneCameraManager(SDL_Window* _context)
	{
		s_Context = _context;
		s_MasterSceneEditorCamera = new MasterSceneEditorCamera(s_Context);

		RegisterCamera(s_MasterSceneEditorCamera->ID, s_MasterSceneEditorCamera->Camera);
	}
	SceneCameraManager::~SceneCameraManager()
	{
		s_CameraCollection.clear();
		delete s_MasterSceneEditorCamera;
	}
	MasterSceneEditorCamera* SceneCameraManager::GetMasterCamera() { return s_MasterSceneEditorCamera; };
	bool SceneCameraManager::HasCamera(uint64_t _uid)
	{
		return s_CameraCollection.find(_uid) != s_CameraCollection.end();
	}
	std::map<uint64_t, Component::CameraComponent*>& SceneCameraManager::GetCameraList()
	{ 
		return s_CameraCollection;
	}
	Component::CameraComponent* SceneCameraManager::RegisterCamera(uint64_t _uid, Component::CameraComponent* _camera)
	{
		if (HasCamera(_uid))
			return nullptr;


		int next_offset = (int)s_CameraCollection.size();
		_camera->SetBufferOffset(next_offset);
		_camera->SetID(_uid);
		s_CameraCollection.insert(std::make_pair(_uid, _camera));

		return s_CameraCollection[_uid];
	}
	Component::CameraComponent* SceneCameraManager::GetCamera(uint64_t _uid)
	{
		if (HasCamera(_uid))
			return s_CameraCollection[_uid];

		return nullptr;
	}
	SDL_Window* SceneCameraManager::GetContextWindow() { return s_Context; };

	void SceneCameraManager::EngagePilotMode(uint64_t _uid)
	{
		if (!HasCamera(_uid))
			return;

		// Set all camera in rest mode
		for (auto cam = s_CameraCollection.begin(); cam != s_CameraCollection.end(); cam++)
		{
			cam->second->SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE::IDEL);
		}

		s_CameraCollection[_uid]->SetFlightState(CameraParameter::CAMERA_FLIGHT_STATE::PILOT);
		s_CameraCollection[_uid]->SetPowerState(CameraParameter::CAMERA_POWER_STATE::ON);
	}
	bool SceneCameraManager::PurgeCamera(uint64_t _uid)
	{
		if (!HasCamera(_uid))
			return false;

		s_CameraCollection.erase(_uid);
		return true;
	}


}