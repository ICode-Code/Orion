#ifndef OE1_SCENE_RENDER_MODE_H_
#define OE1_SCENE_RENDER_MODE_H_


namespace OE1Core
{
	enum class RenderMode : int
	{
		LIT,
		XRAY,

		BASE_COLOR,
		NORMAL,
		METAL,
		ROUGHNESS,
		EMISSION,
		ALPHA,
		AO

	};
}

#endif // !OE1_SCENE_RENDER_MODE_H_
