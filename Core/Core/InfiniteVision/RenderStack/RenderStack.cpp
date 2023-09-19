#include "RenderStack.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRenderStack::~IVRenderStack()
		{

		}


		void IVRenderStack::RegisterOpaqueMesh(lwStaticMeshPkg* _mesh)
		{
			s_OpaqueMeshList.push_back(_mesh);
		}
		void IVRenderStack::RegisterTransparentMesh(lwStaticMeshPkg* _mesh)
		{
			s_TransparentMeshList.push_back(_mesh);
		}

		void IVRenderStack::RemoveOpaqueMesh(uint32_t _package_id)
		{
			// add remove code here
		}
		void IVRenderStack::RemoveTransparentMesh(uint32_t __package_id)
		{
			// add remove code here
		}
	}
}