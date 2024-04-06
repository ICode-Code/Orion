#ifndef OE1_CORE_RENDERABLE_MESH_COMPONENT_H_
#define OE1_CORE_RENDERABLE_MESH_COMPONENT_H_


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <Log.h>



namespace OE1Core
{
	namespace Component
	{
		struct CoreMeshArg
		{
			uint32_t InstanceID;
			uint32_t PackageID;
			GLintptr Offset;
			std::vector<GLuint> GeometryBuffer;
			std::vector<GLuint> MaterialAccessIndices;
		};
		class CoreRenderableMeshComponent
		{
			friend class InspectorComponent;
		public:
			CoreRenderableMeshComponent(CoreMeshArg _arg);

			CoreRenderableMeshComponent(
				const CoreRenderableMeshComponent& _other,
				uint32_t _instance_id,
				GLintptr _offset);
			CoreRenderableMeshComponent(const CoreRenderableMeshComponent& _other) = delete;

			~CoreRenderableMeshComponent();

			void SetOffset(GLintptr _offset);
			GLintptr GetOffset() const;

			virtual void Update(const glm::mat4& _transform) = 0;
			virtual void Update() = 0;

			/// <summary>
			/// The same as Update
			/// </summary>
			virtual void UpdateBuffers() = 0;

			uint32_t GetPackageID() const;
			uint32_t GetUniqueInstanceID() const;

			inline bool operator==(const uint32_t& id) const { return id == m_UniqueInstanceID; }
			inline bool operator==(uint32_t id) { return id == m_UniqueInstanceID; }

		protected:
			/**
			* The offset in the buffer where the mesh data starts. This offset indicates the position within the buffer
			* where the vertex and index data for this specific sub-mesh begins.
			*/
			GLintptr m_Offset = 0;

			/**
			* The index used to retrieve the main static mesh data. The m_MeshID represents the identifier or index of the main static
			* mesh data associated with this MeshComponent. The main static mesh holds all the necessary information for rendering,
			* including the vertex data and instance buffer information. 
			* */
			uint32_t m_PackageID = -1;

			/**
			* The unique ID of this mesh instance. The m_UniqueID is a unique identifier assigned to each mesh instance created or added
			* to the scene. Bascally the the entity converted into uint32_t
			*/
			uint32_t m_UniqueInstanceID = -1;

			
			/*
			* A collection of GL_ARRAY_BUFFER IDs used by this mesh. The number of buffers in the m_Buffers vector
			* corresponds to the number of sub-meshes within a single model.
			*/
			std::vector<GLuint> m_Buffers;

			/**
			* A collection of material IDs corresponding to the sub-meshes within this mesh. Each material ID is associated
			* with a specific sub-mesh, allowing for individual material assignment and customization. The size of the
			* m_MaterialIDs vector is equal to the number of sub-meshes present in the mesh.
			* */
			std::vector<uint32_t> m_MaterialIDs;
		};
	}
}

#endif // !OE1_CORE_RENDERABLE_MESH_COMPONENT_H_
