#include "TagComponent.h"


namespace OE1Core
{
	namespace Component
	{
		TagComponent::TagComponent(std::string _tag, EntityType _type_id)
		{
			m_Type = s_TypeRegistry[_type_id];
			m_EnumType = _type_id;
			m_Identifier = _tag;
			m_RootFullName = m_Identifier;
			if (!m_Type.first.empty() && !m_Type.second.empty())
				RefreshRootName();
		}
		TagComponent::~TagComponent()
		{
		}
		void TagComponent::SetType(EntityType _type_id)
		{ 
			m_Type = s_TypeRegistry[_type_id];
			m_EnumType = _type_id;
			RefreshRootName();
		};
		std::string TagComponent::GetTypeName() { return std::get<0>(m_Type); }
		std::string TagComponent::GetTypeIcon() { return std::get<1>(m_Type); };
		EntityType TagComponent::GetType() const { return m_EnumType; };

		void TagComponent::RefreshRootName()
		{
			std::string temp = GetTypeIcon() + "\t" + m_Identifier;
			m_RootFullName = "\t\t" + temp + "\t\t\t" + GetTypeName();
		}
		std::string TagComponent::GetRootFullName()
		{
			return m_RootFullName;
		}
	}
}