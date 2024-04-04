#include "TurboOTNode.h"


namespace OE1Core
{
	namespace DS
	{
		TurboOTNode::TurboOTNode(glm::vec3 _center, float _size, int _depth, int _child_count)
		{
			m_Center = _center;
			m_Size = _size;
			m_Depth = _depth;
			m_HalfSize = m_Size * 0.5f;
			m_Leaf = true;
			m_NumberOfChild = _child_count;


			//m_Child.reserve(m_NumberOfChild);
			//memset(m_Child, 0, sizeof(m_Child));

			m_Data.reserve(MIN_OBJECT_PER_NODE);

			m_Min = m_Center - m_HalfSize;
			m_Max = m_Center + m_HalfSize;

		}
		TurboOTNode::~TurboOTNode()
		{

		}

		bool TurboOTNode::Has(glm::vec3 _point)
		{
			return (
				_point.x >= m_Min.x && _point.x <= m_Max.x &&
				_point.y >= m_Min.y && _point.y <= m_Max.y &&
				_point.z >= m_Min.z && _point.z <= m_Max.z
				);
		}
		bool TurboOTNode::Register(glm::vec3 _data)
		{

			return false;
		}

		 bool TurboOTNode::Purge(glm::vec3 _data)
		{

			return false;
		}
	}
}