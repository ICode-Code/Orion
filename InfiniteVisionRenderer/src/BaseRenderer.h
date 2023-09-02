#ifndef OE1_BASE_RENDERER_H_
#define OE1_BASE_RENDERER_H_ 

#include "Interface/CoreSystemInterface.h"
#include "Interface/SceneInterface.h"

#include <UniformBuffer/UniformBlockManager.h>
#include <Shader.h>

namespace OE1Core
{
	namespace Renderer
	{
		class __declspec(dllexport) BaseRenderer
		{
		public:
			BaseRenderer(SceneInterface* _scene_interface, CoreSystemInterface* _coreSystem_interface)
				: m_SceneInterface{ _scene_interface }, m_CoreSystemInterface{ _coreSystem_interface }
			{};
			virtual ~BaseRenderer() = default;

		protected:
			OE1Core::Shader* m_Shader = nullptr;
			SceneInterface* m_SceneInterface = nullptr;
			CoreSystemInterface* m_CoreSystemInterface = nullptr;
		};
	}
}

#endif // !OE1_BASE_RENDERER_H_
