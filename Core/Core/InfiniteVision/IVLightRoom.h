#ifndef OE1_IV_LIGHT_ROOM_H_
#define OE1_IV_LIGHT_ROOM_H_

#include "../Core/Texture/TextureCubeMap.h"

namespace OE1Core
{
	namespace Renderer
	{
		struct IVLightRoom
		{
			GLuint IrradianceMap				= 0;
			GLuint PreFilteredEnviromentMap		= 0;
			GLuint LUT							= 0;
			TextureCubeMap* m_ActiveCubeMap		= nullptr;
		};
	}
}

#endif // !OE1_IV_LIGHT_ROOM_H_
