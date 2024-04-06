#ifndef OE1_SKINNED_MESH_COMPONENT_H_
#define OE1_SKINNED_MESH_COMPONENT_H_


#include <GL/glew.h>
#include <Log.h>
#include "../../MeshCluster/DynamicMeshInstancePkg.h"
#include "../CoreRenderableMeshComponent/CoreRenderableMeshComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class SkinnedMeshComponent : public CoreRenderableMeshComponent
		{
			friend class InspectorComponent;
		public:
			SkinnedMeshComponent(CoreMeshArg _arg, uint32_t _armature_id, int _bone_count);
			SkinnedMeshComponent(
				const SkinnedMeshComponent& _other, 
				uint32_t _unique_instance_id, 
				GLintptr _offset,
				uint32_t _armature_id);
			SkinnedMeshComponent(const SkinnedMeshComponent&) = delete;
			~SkinnedMeshComponent();

			void SetArmatureBufferIndex(int _id);
			int GetArmatureBufferID() const;

			virtual void Update(const glm::mat4& _transform) override;
			virtual void Update() override;
			virtual void UpdateBuffers() override;
			DynamicMeshInstancePkg GetInstanceData() const;

		protected:
			bool m_ShowBoundVolume = false;
			int m_BoneCount = 0;
			/* PerInstance Data */
			DynamicMeshInstancePkg m_CoreInstanceData;
		};
	}
}

#endif // !OE1_SKINNED_MESH_COMPONENT_H_
