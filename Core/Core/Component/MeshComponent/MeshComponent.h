#ifndef OE1_MESH_COMPONENT_H_
#define OE1_MESH_COMPONENT_H_

#include <GL/glew.h>
#include <Log.h>
#include "../../MeshCluster/StaticMeshInstancePkg.h"
#include "../CoreRenderableMeshComponent/CoreRenderableMeshComponent.h"

#include <vector>

namespace OE1Core
{
	namespace Component
	{
		class MeshComponent : public CoreRenderableMeshComponent
		{
			friend class InspectorComponent;
		public:
			MeshComponent(CoreMeshArg _arg);

			MeshComponent(
				const MeshComponent& _other, 
				uint32_t _unique_instance_id, 
				GLintptr _offset);

			MeshComponent(const MeshComponent&) = delete;
			~MeshComponent();

			virtual void Update(const glm::mat4& _transform) override;
			virtual void Update() override;;

			StaticMeshInstancePkg GetInstanceData() const;

		protected:
			bool m_ShowBoundVolume = false;
			/* PerInstance Data */
			StaticMeshInstancePkg m_CoreInstanceData;
		};
	}
}

#endif // !OE1_MESH_COMPONENT_H_
