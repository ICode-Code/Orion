#include "TurboOTNode.h"
#include "../Core/Command/CoreCommand/Commnad.h"
#include "LogUI.h"

namespace OE1Core
{
	namespace DS
	{
		TurboOTNode::TurboOTNode(glm::vec3 _center, float _size, int _depth, bool _is_root)
		{
			m_IsRoot = _is_root;
			m_Center = _center;
			m_Size = _size;
			m_HalfSize = m_Size * 0.5f;
			m_Depth = _depth;
			m_Leaf = true;


			for (int i = 0; i < CHILD_PER_OT_NODE; i++)
				m_Child[i] = nullptr;

			m_Data.reserve(MIN_OBJECT_PER_NODE);

			m_Min = m_Center - m_HalfSize;
			m_Max = m_Center + m_HalfSize;


			CommandDef::SceneDebugShapeCreateCommandDef commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
			commandX.Node = this;
			Command::PushSceneDebugShapeCreateCommand(commandX);

		}
		TurboOTNode::~TurboOTNode()
		{
			glDeleteVertexArrays(1, &m_VisualizationVAO);
			m_VisualizationVAO = 0;
			glDeleteBuffers(1, &m_VisualizationVBO);
			m_VisualizationVBO = 0;

			if (!m_Leaf)
				delete[] m_Child;
			m_Leaf = true;

		}

		bool TurboOTNode::CanContain(glm::vec3 _point)
		{
			return (
				_point.x >= m_Min.x && _point.x <= m_Max.x &&
				_point.y >= m_Min.y && _point.y <= m_Max.y &&
				_point.z >= m_Min.z && _point.z <= m_Max.z
				);
		}
		bool TurboOTNode::CanContain(OE1Core::CoreMeshDescriptor::MeshBound _bound, glm::vec3 _scale)
		{

			m_Min *= _scale;
			m_Max *= _scale;

			if (_bound.Min.x >= this->m_Min.x &&
				_bound.Min.y >= this->m_Min.y &&
				_bound.Min.z >= this->m_Min.z) {
				// Check if all maximum coordinates of _bound are less than or equal to this->m_Max
				if (_bound.Max.x <= this->m_Max.x &&
					_bound.Max.y <= this->m_Max.y &&
					_bound.Max.z <= this->m_Max.z) {
					return true; // All conditions met, _bound can be contained
				}
			}

			return false;
		}
		bool TurboOTNode::RegisterChild(OTEntDiscriptor _data)
		{
			bool _can_contain = CanContain(_data.Position);
			bool _can_conatin_bound = CanContain(_data.Bound, _data.Scale);

			if (!_can_contain && !m_IsRoot)
				return false;

			// Make sure the main root node can accomodate this node
			if ((!_can_contain && m_IsRoot) || !_can_conatin_bound)
			{
				// Collect all the data
				std::vector<OTEntDiscriptor> __data;
				CollectData(__data);


				// if this is the root node and can't conatin the entity
				// we need to scale the root node in otHER WORD WE NEED TO RE_BUILD THE TREE

				// Calculate the entity bound with scale factor
				glm::vec3 e_min = _data.Bound.Min * _data.Scale;
				glm::vec3 e_max = _data.Bound.Max * _data.Scale;

				// combined entity 
				glm::vec3 _new_min = glm::min(m_Min, e_min);
				glm::vec3 _new_max = glm::max(m_Max, e_max);
				glm::vec3 _new_size = _new_max - _new_min;

				// get scaling factor
				glm::vec3 _current_size = m_Max - m_Min;
				glm::vec3 _scale_factor = _new_size / _current_size;

				float distance = glm::length(_data.Position - m_Center);

				// Adjust the scaling factor based on the distance
				float distanceFactor = distance / glm::length(_current_size) * 0.5f;
				_scale_factor += glm::vec3(distanceFactor);

				ReBuildTree(glm::max(_scale_factor.x, glm::max(_scale_factor.y, _scale_factor.z)));

				for (auto iter : __data)
					RegisterChild(iter);
			}

			if (m_Data.size() < MIN_OBJECT_PER_NODE && m_Leaf)
			{
				m_Data.push_back(_data);
				return true;
			}

			if (m_Leaf)
			{
				Subdivide();
				DistributeData();
			}

			for (int i = 0; i < CHILD_PER_OT_NODE; i++)
				if (m_Child[i]->RegisterChild(_data))
					return true;


			return false;
		}
		OTEntDiscriptor TurboOTNode::GetData(uint32_t _data_id)
		{
			for (size_t i = 0; i < m_Data.size(); i++)
				if (m_Data[i].EntityID == _data_id)
					return m_Data[i];

			if (!m_Leaf)
				for (int i = 0; i < CHILD_PER_OT_NODE; i++)
				{
					OTEntDiscriptor _res = m_Child[i]->GetData(_data_id);
					if (_res.Valid)
						return _res;
				}

			return OTEntDiscriptor();
		}
		bool TurboOTNode::PurgeChild(uint32_t _data_id)
		{

			for (size_t i = 0; i < m_Data.size(); i++)
			{
				if (m_Data[i].EntityID == _data_id)
				{
					// remove the data
					m_Data.erase(m_Data.begin() + i);
					return true;
				}
			}

			// Search inside the child also

			if (!m_Leaf)
				for (int i = 0; i < CHILD_PER_OT_NODE; i++)
					if (m_Child[i]->PurgeChild(_data_id))
						return true;


			return false;
		}

		 bool TurboOTNode::UpdateChild(uint32_t _id)
		 {

			 return false;
		 }
		 void TurboOTNode::CollectData(std::vector<OTEntDiscriptor>& _buffer)
		 {
			 if(!this->m_Data.empty())
				_buffer.insert(_buffer.end(), this->m_Data.begin(), this->m_Data.end());
			 
			 if (!m_Leaf)
				 for (int i = 0; i < CHILD_PER_OT_NODE; i++)
					 m_Child[i]->CollectData(_buffer);
		 }
		 void TurboOTNode::Subdivide()
		 {
			 float child_size = m_Size * 0.5f;
			 float child_offset[2] = { child_size * 0.5f, -child_size * 0.5f };
			 int _idx = 0;

			 for (auto x : child_offset)
			 {
				 for (auto y : child_offset)
				 {
					 for (auto z : child_offset)
					 {
						 glm::vec3 _child_center = m_Center + glm::vec3(x, y, z);
						// printf("%f, %f, %f\n", _child_center.x, _child_center.y, _child_center.z);
						 m_Child[_idx] = new TurboOTNode(_child_center, child_size, m_Depth + 1);
						 _idx++;
					 }
				 }
			 }
			 m_Leaf = false;
		 }
		 void TurboOTNode::DistributeData()
		 {
			 while (!m_Data.empty())
			 {
				 // For Each Child
				 for (int i = 0; i < CHILD_PER_OT_NODE; i++)
				 {
					 if (m_Child[i]->RegisterChild(m_Data.back()))
						 break;
				 }
				 m_Data.pop_back();

			 }
		 }
		 void TurboOTNode::ReBuildTree(float _new_size)
		 {
			 ReComputeBound(_new_size);

			 // Update Command
			 CommandDef::SceneDebugShapeUpdateCommandDef commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
			 commandX.Node = this;
			 Command::PushSceneDebugShapeUpdateCommand(commandX);

			 if (!m_Leaf)
				 for (int i = 0; i < CHILD_PER_OT_NODE; i++)
					 CleanNodes(m_Child[i]);
			 m_Leaf = true;
		 }
		 void TurboOTNode::ReComputeBound(float _size)
		 {
			 m_Size *= _size;
			 m_HalfSize = m_Size * 0.5f;

			 m_Min = m_Center - m_HalfSize;
			 m_Max = m_Center + m_HalfSize;
		 }
		 void TurboOTNode::CleanNodes(TurboOTNode* _node)
		 {
			 if (!_node->m_Leaf)
			 {
				 for (int i = 0; i < CHILD_PER_OT_NODE; i++)
					 CleanNodes(_node->m_Child[i]);
				 _node->m_Leaf = true;
			 }

			 delete _node;
			 _node = nullptr;
		 }



		 bool TurboOTNode::FrustumIntersect(Frustum& _frustum)
		 {
			 // Iterate over each plane of the frustum
			 for (int i = 0; i < 6; i++)
			 {
				 Plane& plane = _frustum.GetPlane(i);

				 // Find the point in the bounding box that is furthest along the direction of the plane normal
				 glm::vec3 pointInBox = m_Min;
				 if (plane.GetNormal().x >= 0)
					 pointInBox.x = m_Max.x;
				 if (plane.GetNormal().y >= 0)
					 pointInBox.y = m_Max.y;
				 if (plane.GetNormal().z >= 0)
					 pointInBox.z = m_Max.z;

				 // If the furthest point is behind the plane, the entire bounding box is outside the frustum
				 if (plane.GetSignedDistanceToPlace(pointInBox) < 0)
					 return false;
			 }

			 return true;
		 }
		 void TurboOTNode::Filter(Frustum& _frustum, std::unordered_map<uint32_t, std::vector<OTEntDiscriptor>>& _buffers)
		 {
			 bool __intersect = FrustumIntersect(_frustum);

			 if (!__intersect)
				 return;

			 for (size_t i = 0; i < m_Data.size(); i++)
				 _buffers[m_Data[i].PackageID].push_back(m_Data[i]);

			 if (!m_Leaf)
				 for (int i = 0; i < CHILD_PER_OT_NODE; i++)
					 m_Child[i]->Filter(_frustum, _buffers);
		 }
	}
}