#ifndef OE1_RENDERER_SETTING_H_
#define OE1_RENDERER_SETTING_H_


namespace OE1Core
{
	namespace Renderer
	{
		namespace Policy
		{
			inline static constexpr int MIN_RESOLUTION_X = 320;
			inline static constexpr int MIN_RESOLUTION_Y = 240;

			inline static constexpr int MAX_RESOLUTION_X = 2560;
			inline static constexpr int MAX_RESOLUTION_Y = 1440;

			static bool ValidateResolution(int _width, int _height)
			{
				if (_width > MAX_RESOLUTION_X ||
					_width < MIN_RESOLUTION_X ||
					_height > MAX_RESOLUTION_Y ||
					_height < MIN_RESOLUTION_Y)
					return false;
				return true;
			}
		}
	}
}

#endif // !OE1_RENDERER_SETTING_H_
