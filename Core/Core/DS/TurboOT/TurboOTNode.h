#ifndef OE1_TURBO_OCTREE_NODE_H_
#define OE1_TURBO_OCTREE_NODE_H_

#include <vector>
#include <glm/glm.hpp>

#define NUMBER_OF_CHILD 8
#define MIN_OBJECT_PER_NODE 10000

namespace OE1Core
{
	namespace DS
	{
		class TurboOTNode
		{
		public:
			TurboOTNode(glm::vec3 _center, float _size, int _depth, int _child_count = NUMBER_OF_CHILD);
			~TurboOTNode();


			bool Register(glm::vec3 _data);
			bool Purge(glm::vec3 _data);
			


		private:
			bool m_Leaf = true;
			float m_Size;
			float m_HalfSize;
			int m_Depth;
			int m_NumberOfChild = 0;

			std::vector<TurboOTNode*> m_Child;
			std::vector<glm::vec3> m_Data;

			glm::vec3 m_Center;
			glm::vec3 m_Min;
			glm::vec3 m_Max;

		private: // Util
			bool Has(glm::vec3 _point);
		};
	}
}

#endif // !OE1_OCTREE_NODE_H_
