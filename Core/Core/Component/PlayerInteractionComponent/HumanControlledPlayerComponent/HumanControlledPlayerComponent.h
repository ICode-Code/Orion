#ifndef OE1_HUMAN_CONTROLLED_PLAYER_COMPONENT_H_
#define OE1_HUMAN_CONTROLLED_PLAYER_COMPONENT_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

namespace OE1Core
{
	namespace Component
	{
		class HumanControlledPlayerComponent
		{
		public:
			HumanControlledPlayerComponent();
			~HumanControlledPlayerComponent();

		protected:
			uint32_t m_ParentEntity;
		};
	}
}


#endif // !OE1_HUMAN_CONTROLLED_PLAYER_COMPONENT_H_
