#ifndef OE1_DIRECTIONAL_LIGHT_COMPONENT_H_
#define OE1_DIRECTIONAL_LIGHT_COMPONENT_H_

#include "../BaseLightComponent/BaseLightComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class DirectionalLightComponent : public BaseLightComponent
		{
		public:
			DirectionalLightComponent(GLuint _buffer, int _idx = 0);
			DirectionalLightComponent(const DirectionalLightComponent& _other, int _idx);
			~DirectionalLightComponent();

			void Update(glm::vec3 _position, glm::vec3 _rot = glm::vec3(-0.2f, -1.0f, -0.3f)) override;
		};
	}
}

#endif // !OE1_DIRECTIONAL_LIGHT_COMPONENT_H_
