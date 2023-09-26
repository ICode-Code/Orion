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
			TagComponent(std::string _tag = "Untitled", std::pair<std::string, std::string> _type = std::make_pair("", ""));
			~TagComponent();
			inline operator std::string() const { return m_Identifier; }
			void SetType(std::pair<std::string, std::string> _type);
			std::string m_Identifier;
			UUID m_UID;
			std::string GetRootFullName();
			std::string GetTypeName();
			std::string GetTypeIcon();
			void RefreshRootName();
			std::pair<std::string, std::string> m_Type;

		protected:
			std::string m_RootFullName = "";
		};
	}
}

#endif // !OE1_TAG_COMPONENT_H_
