#ifndef OE1_BOUNDING_VOLUME_COMPONENT_H_
#define OE1_BOUNDING_VOLUME_COMPONENT_H_

#include <GL/glew.h>
#include <Log.h>

#include "../../MeshCluster/StaticMeshInstancePkg.h"
#include "../../MeshCluster/CoreMeshDescriptor.h"
#include <glm/glm.hpp>

namespace OE1Core
{
	namespace Component
	{
		class BoundingVolumeComponent
		{
			friend class InspectorComponent;
		public:
			BoundingVolumeComponent(uint32_t _pkg_id, std::vector<GLuint> _buffers, uint32_t _unique_id, GLintptr _offset, glm::vec3 _min, glm::vec3 _max);
			BoundingVolumeComponent(const BoundingVolumeComponent& _other, uint32_t _unique_id, GLintptr _offset);
			~BoundingVolumeComponent();

			void SetOffset(GLintptr _offset);
			GLintptr GetOffset() const;
			void Update(const glm::mat4& _transform);
			void Update();
			
			uint32_t GetPackageID() const;
			uint32_t GetUniqueInstanceID() const;
			StaticMeshInstancePkg GetInstanceCore() const;
			CoreMeshDescriptor::MeshBound GetBound();
			inline bool operator==(const uint32_t& id) const { return id == m_UniqueInstanceID; }
			inline bool operator==(uint32_t id) { return id == m_UniqueInstanceID; }

		private:
			uint32_t m_UniqueInstanceID = -1;
			uint32_t m_PackageID;
			CoreMeshDescriptor::MeshBound m_Bound;
			std::vector<GLuint> m_InstanceBuffers;
			StaticMeshInstancePkg m_CoreInstanceData;
			GLintptr m_Offset = 0;
		};
	}
}

#endif // !OE1_BOUNDING_VOLUME_COMPONENT_H_
