#ifndef OE1_TURBO_OCTREE_H_
#define OE1_TURBO_OCTREE_H_

#include "TurboOTNode.h"

namespace OE1Core
{
	class Entity;
	class Scene;
	namespace DS
	{
		class TurboOT
		{
			friend class Scene;
		public:
			TurboOT();
			~TurboOT();


			void FrustumCull(std::map<std::string, CameraParameters>& _cameras);
			// Add to the structre
			void Register(OTEntDiscriptor _discriptor);

			// When Entity move around
			void Update(Entity _entity);

			// remove from the tree
			void Purge(Entity _entity);

			TurboOTNode& GetRootNode();
			std::unordered_map<uint32_t, std::vector<OTEntDiscriptor>>& GetCulledBuffer();
		private:
			TurboOTNode m_RootNode;
			std::unordered_map<uint32_t, std::vector<OTEntDiscriptor>> m_CulledBuffer;
		};
	}
}


#endif // !OE1_TURBO_OCTREE_H_
