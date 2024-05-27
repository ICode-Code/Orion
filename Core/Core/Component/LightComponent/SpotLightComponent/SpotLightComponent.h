#ifndef OE1_SPOT_LIGHT_COMPONENT_H_
#define OE1_SPOT_LIGHT_COMPONENT_H_

#include "../BaseLightComponent/BaseLightComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class SpotLightComponent : public BaseLightComponent
		{
		public:
			SpotLightComponent(GLuint _buffer, int _idx);
			SpotLightComponent(const SpotLightComponent& _other, int _idx);
			~SpotLightComponent();

			void Update(glm::vec3 _position, glm::vec3 _rot = glm::vec3(-0.2f, -1.0f, -0.3f)) override;
		};
	}
}

#endif // !OE1_SPOT_LIGHT_COMPONENT_H_
