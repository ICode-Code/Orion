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

		void UpdateData(GeometryPacket::IVModelSkinnedModelData* _geometry_packet);

		void SetActiveAnimation(std::string _name);
		Animation* GetActiveAnimation();

		void RegisterAnimation(Animation* _animation);
		void PurgeAnimation(std::string _name);
		Animation* GetAnimation(std::string _name);
		std::unordered_map<std::string, Animation*>& GetAnimationList();

		static void InterpolateAnimation(Animation* a, Animation* b, float time);

	private:
		uint32_t m_AnimationBuffer;
		int m_AnimationCount = 0;

		Animation* m_ActiveAnimation = nullptr;
		std::unordered_map<std::string, Animation*> m_AnimationList;
		
	};
}


#endif // !OE1_DYNAMIC_MES_H_
