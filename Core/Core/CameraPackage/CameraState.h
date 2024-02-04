#ifndef OE1_CAMERA_STATE_H_
#define OE1_CAMERA_STATE_H_

namespace OE1Core
{
	namespace CameraState
	{
		enum class Power
		{
			ON,
			OFF
		};

		enum class FlightState
		{
			PILOT,
			REST
		};
	}
}

#endif // !OE1_CAMERA_STATE_H_
