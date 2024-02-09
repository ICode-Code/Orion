#ifndef OE1_SCENE_CAMERA_MANAGER_H_
#define OE1_SCENE_CAMERA_MANAGER_H_

#include <map>

#include "../../CameraPackage/CameraPackage.h"


namespace OE1Core
{
	class SceneCameraManager
	{
	public:
		// Initialization of Camera named "MasterCamera" is guaranteed
		SceneCameraManager(SDL_Window* _window);
		~SceneCameraManager();

		/// <summary>
		/// DO NOT CALL THIS FUNCTION INSIDE ATTACHNED
		/// FRAMEBUFFER, JUST CALL IT BEFORE ATTACHING FRAMBUFFER
		/// AND ALSO NEED TO BE CALLED WITH ACTIVE OPENGL CONTEXT
		/// </summary>
		/// <param name="_name"></param>
		/// <param name="_init_pos"></param>
		/// <returns></returns>
		CameraPackage* RegisterCamera(std::string _name, glm::vec3 _init_pos = glm::vec3(0.0f, 5.0f, 0.0f));

		CameraPackage* GetCamera(std::string _name);

		void EngagePilotMode(std::string _name);
		bool PurgeCamera(std::string _name);

		
		/// <summary>
		/// Make sure it exist before calling this
		/// or you will crash the program
		/// </summary>
		/// <param name="_name"></param>
		/// <returns></returns>
		CameraParameters& GetCameraWithParameters(std::string _name);
		/// <summary>
		/// This will return -1, if the _name is invalid be Aware
		/// </summary>
		/// <param name="_name"></param>
		/// <returns></returns>
		int GetCameraIndex(std::string _name);
		bool HasCamera(std::string _name);
		std::map<std::string, CameraParameters>& GetCameraList(); 


	private:
		std::map<std::string, CameraParameters> m_CameraList;
		SDL_Window* m_Context = nullptr;

	};
}

#endif // !OE1_SCENE_CAMERA_MANAGER_H_
