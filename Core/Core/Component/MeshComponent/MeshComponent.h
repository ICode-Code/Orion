#ifndef OE1_MESH_COMPONENT_H_
#define OE1_MESH_COMPONENT_H_

#include <GL/glew.h>
#include <Log.h>
#include "../../MeshCluster/StaticMeshInstancePkg.h"

#include <vector>

namespace OE1Core
{
	namespace Component
	{
		class MeshComponent
		{
			friend class InspectorComponent;
		public:
			MeshComponent(uint32_t _package_id, uint32_t _unique_instance_id, GLintptr _offset, std::vector<GLuint> _geometry_buffers, std::vector<uint32_t> _mat_offsets);
			MeshComponent(const MeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset);
			MeshComponent(const MeshComponent&) = delete;
			~MeshComponent();

			void SetOffset(GLintptr _offset);
			GLintptr GetOffset() const;
			void Update(const glm::mat4& _transform);
			void Update();

			uint32_t GetPackageID() const;
			uint32_t GetUniqueInstanceID() const;
			StaticMeshInstancePkg GetInstanceCore() const;

			inline bool operator==(const uint32_t& id) const { return id == m_UniqueInstanceID; }
			inline bool operator==(uint32_t id) { return id == m_UniqueInstanceID; }


		protected:
			bool m_ShowBoundVolume = false;
		protected:
			/**
			* The offset in the buffer where the mesh data starts. This offset indicates the position within the buffer
			* where the vertex and index data for this specific sub-mesh begins. It allows efficient access to the relevant
			* data within the buffer, enabling proper rendering of the sub-mesh.
			*
			* The m_Offset value is typically specified as an integer value representing the byte offset from the start of the buffer.
			* By using the offset, the graphics pipeline can locate the appropriate data within the buffer for rendering the sub-mesh,
			* ensuring correct alignment and data retrieval.
			*/
			GLintptr m_Offset = 0;

			/**
			* The index used to retrieve the main static mesh data. The m_MeshID represents the identifier or index of the main static
			* mesh data associated with this MeshComponent. The main static mesh holds all the necessary information for rendering,
			* including the vertex data and instance buffer information. The m_MeshID allows efficient retrieval of the required data
			* when rendering or performing operations on this specific mesh component.
			* */
			uint32_t m_PackageID = -1;

			/**
			* The unique ID of this mesh instance. The m_UniqueID is a unique identifier assigned to each mesh instance created or added
			* to the scene. It distinguishes and identifies this specific instance among other instances of the same mesh. This ID is
			* useful for various purposes, such as managing and tracking individual instances, applying instance-specific properties
			* or modifications, and facilitating communication or interaction with specific instances within the application or system.
			*/
			uint32_t m_UniqueInstanceID = -1;

			/**
			* The core data associated with this mesh. The m_CoreData is a structure or object that holds the essential data associated
			* with this mesh instance. It is stored per instance inside a buffer and typically includes information such as the transform,
			* instance ID, and material ID. The transform represents the position, orientation, and scale of the mesh instance in the scene.
			* The instance ID allows identification of this specific mesh instance among others. The material ID specifies the material
			* assigned to this mesh instance, determining its visual appearance. The m_CoreData provides the fundamental data required
			* for rendering and manipulation of this mesh instance within the graphics pipeline.*/
			StaticMeshInstancePkg m_CoreInstanceData;

			/**
			* A collection of GL_ARRAY_BUFFER IDs used by this mesh. The number of buffers in the m_Buffers vector
			* corresponds to the number of sub-meshes within a single model. For example, if a car model consists of multiple
			* sub-meshes such as the body, engine, and glass, each of these sub-meshes will have its own dedicated buffer.
			*
			* Each buffer within m_Buffers stores the vertex and index data required for rendering a specific sub-mesh. By separating
			* the data into individual buffers, it allows for efficient memory management and targeted updates to specific sub-meshes.
			* This organization facilitates flexibility in rendering and provides a means to optimize rendering performance by only
			* updating or rendering the necessary sub-meshes.
			*
			* The buffer IDs stored in m_Buffers are typically associated with the vertex and index data required for rendering a specific
			* sub-mesh. These buffers enable the graphics pipeline to access the geometry and attributes associated with each sub-mesh
			* during the rendering process. It is important to ensure that the size and ordering of the buffers in m_Buffers correspond
			* correctly with the sub-meshes' material IDs in the m_MaterialIDs vector.
			*
			* When rendering the mesh, the appropriate buffer from m_Buffers is bound before issuing the draw call for each sub-mesh.
			* This ensures that the correct vertex and index data are accessed for rendering each individual sub-mesh, achieving
			* the desired visual representation of the complete mesh.
			*/
			std::vector<GLuint> m_Buffers;

			/**
			* A collection of material IDs corresponding to the sub-meshes within this mesh. Each material ID is associated
			* with a specific sub-mesh, allowing for individual material assignment and customization. The size of the
			* m_MaterialIDs vector is equal to the number of sub-meshes present in the mesh.
			*
			* In a scenario where a complex model, like a car, is represented by multiple sub-meshes such as the body, engine,
			* and glass, each of these sub-meshes will have its own dedicated material ID. This organization enables fine-grained
			* control over the appearance of each sub-mesh, including properties such as textures, shaders, and other material
			* attributes.
			*
			* By referencing the material IDs, it becomes convenient to apply specific materials to individual sub-meshes or group
			* multiple sub-meshes under the same material, depending on the desired visual representation. This allows for
			* flexible rendering setups and easy management of materials within the mesh component.
			*
			* Note that the m_MaterialIDs vector should have the same size as the m_Buffers vector, ensuring that each sub-mesh has
			* a corresponding material ID and buffer. Proper synchronization between these vectors is essential for correct rendering
			* and associating the correct materials with the respective sub-meshes.
			*/
			std::vector<uint32_t> m_MaterialIDs;
		};
	}
}

#endif // !OE1_MESH_COMPONENT_H_
