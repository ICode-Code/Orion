#ifndef OE1_IV_BASE_RENDERER_H_
#define OE1_IV_BASE_RENDERER_H_

#include "../../Material/MaterialManager.h"
#include <ShaderManager/ShaderManager.h>
#include "../../../Common/Shared/ViewportArgs.h"
#include "../../MeshCluster/CoreStaticMeshPkg.h"
#include "../../MeshCluster/lwStaticMeshPkg.h"
#include "../RenderStack/RenderStack.h"

namespace OE1Core
{
	namespace Renderer
	{
		class IVBaseRenderer
		{
		public:
			IVBaseRenderer() {};
			virtual ~IVBaseRenderer() {};

		protected:
			OE1Core::Shader* m_Shader = nullptr;
		};
	}
}

#endif // !OE1_IV_BASE_RENDERER_H_
