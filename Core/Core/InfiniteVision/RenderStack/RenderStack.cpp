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

		void IVRenderStack::RemoveOpaqueMesh(MaterialType _type)
		{
			if (s_OpaqueMeshList.find(_type) != s_OpaqueMeshList.end())
				s_OpaqueMeshList.erase(_type);
		}
		void IVRenderStack::RemoveTransparentMesh(MaterialType _type)
		{
			if (s_TransparentMeshList.find(_type) != s_TransparentMeshList.end())
				s_TransparentMeshList.erase(_type);
		}
	}
}