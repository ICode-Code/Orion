#ifndef OE1_CAMERA_PARAMETER_H_
#define OE1_CAMERA_PARAMETER_H_

namespace OE1Core
{
	namespace CameraParameter
	{
		// Camera controller types used for this camera component
		enum class CAMERA_CONTROLLER_TYPE
		{
			THIRD_PERSON,
			FIRST_PERSON,
			ORBITAL,
			FREE_LOOK
		};

		// Different types of camera tasks or purposes
		enum class CAMERA_TASK_TYPE
		{
			EDITOR,// Used when the camera is intended for scene editing
			CINEMA,// Used when the camera is intended for cinematic shots
			PLAYER // Used when the camera is intended for player perspective
		};

		// Camera power states used by the rendere or any other intersted party
		enum class CAMERA_POWER_STATE
		{
			ON, // Indicates that the camera is powered on and the renderer should render the active scene to its perspective
			OFF // Indicates that the camera is powered off and no rendering should be done for its perspective
		};

		// Camera flight states indicating controller engagement
		enum class CAMERA_FLIGHT_STATE
		{
			PILOT, // Indicates that the camera is engaged with the controller and can receive controller commands
			IDEL  // Indicates that the camera is not engaged with the controller and will not receive controller commands
		};
	}
}

#endif // !OE1_CAMERA_PARAMETER_H_
