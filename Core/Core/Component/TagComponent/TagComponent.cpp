#include "TagComponent.h"


namespace OE1Core
{
	namespace Component
	{
		TagComponent::TagComponent(std::string _tag)
		{
			m_Identifier = _tag;
		}
		TagComponent::~TagComponent()
		{
		}
	}
}