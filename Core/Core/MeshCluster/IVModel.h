#ifndef OE1_IV_MODEL_H_
#define OE1_IV_MODEL_H_


#include "CoreRenderableMesh.h"
#include <vector>

namespace OE1Core
{
	struct IVModel
	{
	public:
		std::string Name;

		uint32_t PackageID;
		
		glm::vec3 Extent;
		
		CoreMeshDescriptor::MeshBound Bound;
		CoreMeshDescriptor::CoreMeshType Type;

		int SubMeshCount = 0;
		int TotalVertexCount = 0;
		int TotalIndicesCount = 0;
		int TotalTriangleCount = 0;
		

		unsigned int Preview;

		std::vector<CoreRenderableMeshPackage> SubMeshs;


	public: // Util functions
		/// <summary>
		/// Call this after pupulating the sub mesh
		/// </summary>
		/// <param name="_type"></param>
		inline void SetMeshType(CoreMeshDescriptor::CoreMeshType _type)
		{
			Type = _type;
			for (size_t i = 0; i < SubMeshs.size(); i++)
				SubMeshs[i].MeshType = Type;
		}
	};
}

#endif // !OE1_IV_MODEL_H_
