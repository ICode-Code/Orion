#ifndef OE1_STATIC_MESH_H_
#define OE1_STATIC_MESH_H_


#include "../CoreMesh/CoreMesh.h"

namespace OE1Core
{
	class StaticMesh : public CoreMesh
	{
		friend class Renderer::IVMasterRenderer;
	public:
		StaticMesh(IVModel* _model);
		~StaticMesh();

		virtual uint32_t AddInstance(class Entity* _entity) override;
		virtual void PurgeInstance(uint32_t _instanceID, class Scene* _scene) override;
	};
}


#endif // !OE1_STATIC_MESH_H_
