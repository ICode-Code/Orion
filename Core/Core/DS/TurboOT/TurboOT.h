#ifndef OE1_TURBO_OCTREE_H_
#define OE1_TURBO_OCTREE_H_

#include "TurboOTNode.h"

namespace OE1Core
{
	class Entity;
	namespace DS
	{
		class TurboOT
		{
		public:
			TurboOT();
			~TurboOT();


			// Add to the structre
			void Register(Entity _entity);

			// When Entity move around
			void Update(Entity _entity);

			// remove from the tree
			void Purge(Entity _entity);

			TurboOTNode& GetRootNode();
		private:
			TurboOTNode m_RootNode;
		};
	}
}


#endif // !OE1_TURBO_OCTREE_H_
