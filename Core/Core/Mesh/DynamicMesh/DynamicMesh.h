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

		void UpdateData(GeometryPacket::IVModelSkinnedModelData* _geometry_packet);


		void RegisterAnimation(Animation* _animation);
		void PurgeAnimation(std::string _name);
		Animation* GetAnimation(std::string _name);
		std::unordered_map<std::string, Animation*>& GetAnimationList();


	private:
		int m_AnimationCount = 0;
		std::unordered_map<std::string, Animation*> m_AnimationList;
		
	};
}


#endif // !OE1_DYNAMIC_MES_H_
