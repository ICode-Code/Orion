#ifndef OE1_CORE_RENDERABLE_MESH_H_
#define OE1_CORE_RENDERABLE_MESH_H_

#include "CoreMeshDescriptor.h"
#include "../Material/MasterMaterial.h"

namespace OE1Core
{
    struct CoreRenderableMeshPackage {

        unsigned int VAO;  // Vertex Array Object ID
        unsigned int VBO;  // Vertex Buffer Object ID
        unsigned int EBO;  // Element Buffer Object ID
        unsigned int IBO;  // Index Buffer Object ID

        int TriangleCount = 0;  // Number of triangles in the mesh
        int VertexCount = 0;    // Number of vertices in the mesh
        int IndicesCount = 0;   // Number of indices in the mesh

        uint32_t LocalMeshID;       // Unique identifier for the sub-mesh within a model
        uint32_t PackageID;         // Index to retrieve the model package from the buffer
        uint32_t MaterialID;        // Identifier for the material applied to the mesh
        uint32_t GeometryPacketID;  // Index to get the actual vertex, normal, tangent, etc., data

        CoreMeshDescriptor::MeshBound Bound;  // Boundary of the mesh
        CoreMeshDescriptor::CoreMeshType MeshType;  // Type of the mesh 
        MasterMaterial* Material = nullptr;  // Material applied to the mesh
        std::string Name;  // Name of the mesh

    };

}

#endif // !OE1_CORE_RENDERABLE_MESH_H_
