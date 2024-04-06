#include "DebugOTInit.h"
#include "../TurboOT/TurboOTNode.h"

namespace OE1Core
{
	namespace DS
	{
		void DebugOTInit::Init(class TurboOTNode& _node)
		{

			std::vector<glm::vec3> Position;

			glm::vec3 _min = _node.m_Min;
			glm::vec3 _max = _node.m_Max;


			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));

			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));

			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));


			glGenVertexArrays(1, &_node.m_VisualizationVAO);
			glBindVertexArray(_node.m_VisualizationVAO);

			glGenBuffers(1, &_node.m_VisualizationVBO);

			glBindBuffer(GL_ARRAY_BUFFER, _node.m_VisualizationVBO);
			glBufferData(GL_ARRAY_BUFFER, Position.size() * sizeof(glm::vec3), &Position[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
		void DebugOTInit::Update(class TurboOTNode& _node)
		{
			std::vector<glm::vec3> Position;

			glm::vec3 _min = _node.m_Min;
			glm::vec3 _max = _node.m_Max;


			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));

			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));

			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _max.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _max.y, _min.z));

			Position.push_back(glm::vec3(_min.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _min.z));
			Position.push_back(glm::vec3(_max.x, _min.y, _max.z));
			Position.push_back(glm::vec3(_min.x, _min.y, _max.z));


			glBindVertexArray(_node.m_VisualizationVAO);

			glBindBuffer(GL_ARRAY_BUFFER, _node.m_VisualizationVBO);
			glBufferData(GL_ARRAY_BUFFER, Position.size() * sizeof(glm::vec3), &Position[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}
	}
}