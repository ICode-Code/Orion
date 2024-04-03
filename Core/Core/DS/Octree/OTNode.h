#ifndef OE1_OCTREE_NODE_H_
#define OE1_OCTREE_NODE_H_


#include <glm/glm.hpp>
#include <vector>

#define NUMBER_OF_CHILD 8
#define MIN_OBJECT_PER_NODE 500

namespace OE1Core
{
	namespace DS
	{
		template <typename T> class OTNode
		{
		public:
			OTNode(glm::vec3 _center, float _size, int _depth, int _child_count = NUMBER_OF_CHILD);
			~OTNode();


			bool Register(T _data);
			bool Purge(T _data);
			


		private:
			bool m_Leaf = true;
			float m_Size;
			float m_HalfSize;
			int m_Depth;
			int m_NumberOfChild = 0;

			std::vector<OTNode*> m_Child;
			std::vector<T> m_Data;

			glm::vec3 m_Center;
			glm::vec3 m_Min;
			glm::vec3 m_Max;

		private: // Util
			bool Has(glm::vec3 _point);
		};
	}
}

#endif // !OE1_OCTREE_NODE_H_
