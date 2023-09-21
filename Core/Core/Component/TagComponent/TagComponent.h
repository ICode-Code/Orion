#ifndef OE1_TAG_COMPONENT_H_
#define OE1_TAG_COMPONENT_H_

#include <string>
#include "../../UUID/UUID.h"

namespace OE1Core
{
	namespace Component
	{
		class TagComponent
		{
			friend class InspectorComponent;
		public:
			TagComponent(std::string _tag = "Untitled");
			~TagComponent();
			inline operator std::string() const { return m_Identifier; }
			std::string m_Identifier;
			UUID m_UID;
		};
	}
}

#endif // !OE1_TAG_COMPONENT_H_
