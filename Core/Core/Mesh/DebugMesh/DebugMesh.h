#ifndef OE1_DEBUG_MESH_H_
#define OE1_DEBUG_MESH_H_



#include "../CoreMesh/CoreMesh.h"
#include "../../MeshCluster/CoreDebugShape.h"

namespace OE1Core
{
	class DebugMesh : public CoreMesh
	{
		friend class Renderer::IVMasterRenderer;
	public:
		DebugMesh(IVModel* _model);
		~DebugMesh();

		virtual uint32_t AddInstance(class Entity* _entity) override;
		virtual void PurgeInstance(uint32_t _instanceID, class Scene* _scene) override;

		uint64_t GetShapeID();
		void SetShapeID(uint64_t _id);

		GLenum GetDrawMode();
		void SetDrawMode(GLenum _mode);

	protected:
		GLenum m_DrawMode;
		uint64_t m_ShapeID;
	};
}

#endif // !OE1_DEBUG_MESH_H_
