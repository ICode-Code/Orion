#ifndef OE1_WINDOW_DATA_H_
#define OE1_WINDOW_DATA_H_


struct GLFWwindow;

namespace OE1Core
{
	struct WindowArg
	{
		GLFWwindow* Win;
		int Width;
		int Height;
		bool Running = false;
		const char* Name;
		float ClearColor[4]{ 0.1f, 0.1f, 0.1f, 1.0f };
	};
}

#endif // !OE1_WINDOW_DATA_H_
