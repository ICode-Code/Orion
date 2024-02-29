#ifndef OE1_DYNAMIC_MES_H_
#define OE1_DYNAMIC_MES_H_

#include "../AssetManager/GeometryAssetPacketBuffer/GeometryAssetPacketBuffer.h"
#include "Animation/Animation.h"
#include "../CoreMesh/CoreMesh.h"

namespace OE1Core
{
	class DynamicMesh : public CoreMesh
	{
		friend class Renderer::IVMasterRenderer;
		friend class SceneEntityFactory;
		friend class Scene;
	public:
		DynamicMesh(IVModel* _model);
		~DynamicMesh();

		virtual uint32_t AddInstance(class Entity* _entity) override;
		virtual void PurgeInstance(uint32_t _instanceID, class Scene* _scene) override;

		uint32_t GetAnimationBuffer();
		uint32_t GetAnimationBuffer() const;

	private:
		uint32_t m_AnimationBuffer;

		Animation* m_Animation = nullptr;
		
	};
}


#endif // !OE1_DYNAMIC_MES_H_
