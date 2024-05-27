#include "PointLightComponent.h"


namespace OE1Core
{
	namespace Component
	{
		PointLightComponent::PointLightComponent(GLuint _buffer, int _idx)
			: BaseLightComponent{ _buffer, _idx}
		{

		}
		PointLightComponent::PointLightComponent(const PointLightComponent& _other, int _idx)
			: BaseLightComponent{ _other.m_BufferID, _idx }
		{
			m_Light = _other.m_Light;
		}
		PointLightComponent::~PointLightComponent()
		{

		}
	}
}