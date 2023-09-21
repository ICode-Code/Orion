#include "RenderStack.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRenderStack::~IVRenderStack()
		{

		}


		void IVRenderStack::RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, MaterialType _type)
		{
			if (s_OpaqueMeshList.find(_type) == s_OpaqueMeshList.end())
				s_OpaqueMeshList.insert(std::make_pair(_type, std::make_pair(_mesh->Material->GetShader(), std::vector<lwStaticMeshPkg*>())));

			std::get<1>(s_OpaqueMeshList[_type]).push_back(_mesh);
		}
		void IVRenderStack::RegisterTransparentMesh(lwStaticMeshPkg* _mesh, MaterialType _type)
		{
			if (s_TransparentMeshList.find(_type) == s_TransparentMeshList.end())
				s_TransparentMeshList.insert(std::make_pair(_type, std::make_pair(_mesh->Material->GetShader(), std::vector<lwStaticMeshPkg*>())));

			std::get<1>(s_TransparentMeshList[_type]).push_back(_mesh);
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