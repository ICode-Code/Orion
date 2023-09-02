#ifndef OE1_INTERFACE_H_
#define OE1_INTERFACE_H_

#include "Interface/SceneInterface.h"
#include "Interface/CoreSystemInterface.h"

namespace OE1Core
{
	namespace Renderer
	{
		class Interface
		{
		public:
			Interface(SceneInterface* _sceneI, CoreSystemInterface* _corI)
			{
				m_CoreInterface = _corI;
				m_SceneInterface = _sceneI;
			}

			inline static SceneInterface* m_SceneInterface = nullptr;
			inline static CoreSystemInterface* m_CoreInterface = nullptr;
		};
	}
}

#endif // !OE1_INTERFACE_H_
