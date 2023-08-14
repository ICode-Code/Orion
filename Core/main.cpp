

#include <Log.h>

#include "Common/CoreEngine.h"

int main(int argc, char** argv)
{
	OE1Core::Log::Init(); // Log

	OE1Core::WindowManager __windowManager; // Window Handler

    OE1Core::CoreEngine __coreEngine(argc, argv); //Core Engine 
	__coreEngine.Run();

	return 0;
}