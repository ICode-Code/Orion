#include "SceneCameraManager.h"


namespace OE1Core
{
	SceneCameraManager::SceneCameraManager(SDL_Window* _context)
	{
		m_Context = _context;

		// Create Master Camera
		RegisterCamera("MasterCamera");
	}
	SceneCameraManager::~SceneCameraManager()
	{
		for (auto _camera : m_CameraList)
			delete _camera.second.Camera;

		m_CameraList.clear();
	}
	bool SceneCameraManager::HasCamera(std::string _name)
	{
		return m_CameraList.find(_name) != m_CameraList.end();
	}
	std::unordered_map<std::string, CameraParameters>& SceneCameraManager::GetCameraList()
	{
		return m_CameraList;
	}
	CameraPackage* SceneCameraManager::RegisterCamera(std::string _name, glm::vec3 _init_pos)
	{
		if (HasCamera(_name))
			return nullptr;

		CameraParameters _params;

		_params.Camera = new CameraPackage(m_Context);
		_params.Offset = static_cast<uint32_t>(m_CameraList.size());

		m_CameraList.insert(std::make_pair(_name, _params));

		return m_CameraList[_name].Camera;
	}
	CameraPackage* SceneCameraManager::GetCamera(std::string _name)
	{
		if (HasCamera(_name))
			return m_CameraList[_name].Camera;

		return nullptr;
	}
	CameraParameters& SceneCameraManager::GetCameraWithParameters(std::string _name)
	{
		return m_CameraList[_name];
	}
	int SceneCameraManager::GetCameraIndex(std::string _name)
	{
		if (HasCamera(_name))
			return m_CameraList[_name].Offset;

		return -1;
	}


}