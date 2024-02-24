#ifndef OE1_DYNAMIC_MES_H_
#define OE1_DYNAMIC_MES_H_

#include "../CoreMesh/CoreMesh.h"

namespace OE1Core
{
	class DynamicMesh : public CoreMesh
	{
		friend class Renderer::IVMasterRenderer;
	public:
		DynamicMesh(IVModel* _model);
		~DynamicMesh();

		virtual uint32_t AddInstance(class Entity* _entity) override;
		virtual void PurgeInstance(uint32_t _instanceID, class Scene* _scene) override;

	};
}


#endif // !OE1_DYNAMIC_MES_H_
