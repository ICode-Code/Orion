#ifndef OE1_POINT_LIGHT_COMPONENT_H_
#define OE1_POINT_LIGHT_COMPONENT_H_


#include "../BaseLightComponent/BaseLightComponent.h"

namespace OE1Core
{
	namespace Component
	{
		class PointLightComponent : public BaseLightComponent
		{
		public:
			PointLightComponent(GLuint _buffer_id, int _idx = 0);
			PointLightComponent(const PointLightComponent& _other, int _idx);
			~PointLightComponent();
		};
	}
}

#endif // !OE1_POINT_LIGHT_COMPONENT_H_
