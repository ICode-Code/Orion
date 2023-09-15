#ifndef OE1_GRID_H_
#define OE1_GRID_H_

#include <glm/glm.hpp>
#include "../Common/Shared/UniformBlocks.h"
#include "UniformBuffer/UniformBlockManager.h"

namespace OE1Core
{
	namespace Renderer { class IVGridRenderer; }
	class Grid
	{
		friend class Renderer::IVGridRenderer;
	public:
		Grid();
		~Grid();

		void Update();

	protected:
		unsigned int m_VAO;
		glm::vec4 m_ColorBold = glm::vec4(0.55f, 0.55f, 0.55f, 1.0f);
		glm::vec4 m_ColorLight = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);
		glm::vec3 m_Background = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
		float m_Scale = 500.0f;

	};
}

#endif // !OE1_GRID_H_
