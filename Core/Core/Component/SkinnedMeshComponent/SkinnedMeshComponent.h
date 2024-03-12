#ifndef OE1_SKINNED_MESH_COMPONENT_H_
#define OE1_SKINNED_MESH_COMPONENT_H_


#include <GL/glew.h>
#include <Log.h>
#include "../../MeshCluster/DynamicMeshInstancePkg.h"

namespace OE1Core
{
	namespace Component
	{
		class SkinnedMeshComponent
		{
			friend class InspectorComponent;
		public:
			SkinnedMeshComponent(
				uint32_t _package_id, 
				uint32_t _unique_instance_id, 
				GLintptr _offset, 
				uint32_t _armature_id, 
				int _bone_count,
				std::vector<GLuint> _geometry_buffers, 
				std::vector<uint32_t> _mat_offsets);
			SkinnedMeshComponent(const SkinnedMeshComponent& _other, uint32_t _unique_instance_id, GLintptr _offset);
			SkinnedMeshComponent(const SkinnedMeshComponent&) = delete;
			~SkinnedMeshComponent();

			void SetArmatureBufferIndex(int _id);
			uint32_t GetArmatureBufferID() const;
			void SetOffset(GLintptr _offset);
			GLintptr GetOffset() const;
			void Update(const glm::mat4& _transform);
			void Update();

			uint32_t GetPackageID() const;
			uint32_t GetUniqueInstanceID() const;
			DynamicMeshInstancePkg GetInstanceCore() const;

			inline bool operator==(const uint32_t& id) const { return id == m_UniqueInstanceID; }
			inline bool operator==(uint32_t id) { return id == m_UniqueInstanceID; }


		protected:
			int m_BoneCount = 0;

			GLintptr m_Offset = 0;

			uint32_t m_PackageID = -1;

			uint32_t m_ArmatureBufferID = -1;

			
			uint32_t m_UniqueInstanceID = -1;

			DynamicMeshInstancePkg m_CoreInstanceData;

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

#endif // !OE1_SKINNED_MESH_COMPONENT_H_
