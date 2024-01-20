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

		IVRenderStack::IVDrawList* IVRenderStack::GetDrawList(MaterialType _type, bool _start_with_opaque)
		{
			if (_start_with_opaque)
			{
				if (this->s_OpaqueMeshList.find(_type) != this->s_OpaqueMeshList.end())
					return &s_OpaqueMeshList[_type];

				if (this->s_TransparentMeshList.find(_type) != this->s_TransparentMeshList.end())
					return &s_TransparentMeshList[_type];
			}
			else
			{
				if (this->s_TransparentMeshList.find(_type) != this->s_TransparentMeshList.end())
					return &s_TransparentMeshList[_type];

				if (this->s_OpaqueMeshList.find(_type) != this->s_OpaqueMeshList.end())
					return &s_OpaqueMeshList[_type];
			}

			return nullptr;
		}
		void IVRenderStack::SearchAndDestroy(MaterialType _type)
		{
			if (this->s_OpaqueMeshList.find(_type) != this->s_OpaqueMeshList.end())
				s_OpaqueMeshList.erase(_type);

			if (this->s_TransparentMeshList.find(_type) != this->s_TransparentMeshList.end())
			{
				s_TransparentMeshList.erase(_type);
			}
		}
	}
}