#ifndef OE1_TURBO_OCTREE_NODE_H_
#define OE1_TURBO_OCTREE_NODE_H_

#include "OTEntDiscriptor.h"
#include "../OptStructure/Frustum/Frustum.h"
#include "../Core/CameraPackage/CameraPackage.h"

#include <vector>
#include <map>
#include <string>

#define CHILD_PER_OT_NODE 8
#define MIN_OBJECT_PER_NODE 5
#define MAX_SIZE 5

namespace OE1Core
{
	namespace Renderer { class IVSceneDebugShapeRenderer; }
	namespace DS
	{

		class TurboOTNode
		{
			friend class Renderer::IVSceneDebugShapeRenderer;
			friend class DebugOTInit;
		public:
			TurboOTNode(glm::vec3 _center, float _size = MAX_SIZE, int _depth = 0, bool _is_root = false);
			~TurboOTNode();


			bool RegisterChild(OTEntDiscriptor _data);
			bool PurgeChild(uint32_t _data);
			bool UpdateChild(uint32_t _id);
			void CollectData(std::vector<OTEntDiscriptor>& _buffer);
			OTEntDiscriptor GetData(uint32_t _data_id);
			void Filter(Frustum& _frustum, std::unordered_map<uint32_t, std::vector<OTEntDiscriptor>>& _buffers);
			


		private:
			bool m_Leaf = true;
			float m_Size;
			float m_HalfSize;
			int m_Depth;
			bool m_IsRoot = false;

			
			TurboOTNode* m_Child[CHILD_PER_OT_NODE];
			std::vector<OTEntDiscriptor> m_Data;

			glm::vec3 m_Center;
			glm::vec3 m_Min;
			glm::vec3 m_Max;

			unsigned int m_VisualizationVAO = 0;
			unsigned int m_VisualizationVBO = 0;

		private: // Util
			bool CanContain(glm::vec3 _point);
			bool CanContain(OE1Core::CoreMeshDescriptor::MeshBound _bound, glm::vec3 _scale);
			void Subdivide();
			void DistributeData();
			void ReBuildTree(float _new_size);
			void ReComputeBound(float _size);
			void CleanNodes(TurboOTNode* _node);

		private: // cull
			bool FrustumIntersect(Frustum& _frustum);
		};
	}
}

#endif // !OE1_OCTREE_NODE_H_
