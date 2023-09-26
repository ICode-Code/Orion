#include "TagComponent.h"


namespace OE1Core
{
	namespace Component
	{
		TagComponent::TagComponent(std::string _tag, std::pair<std::string, std::string> _type)
		{
			m_Type = _type;
			m_Identifier = _tag;
			m_RootFullName = m_Identifier;
			if (!m_Type.first.empty() && !m_Type.second.empty())
				RefreshRootName();
		}
		TagComponent::~TagComponent()
		{
		}
		void TagComponent::SetType(std::pair<std::string, std::string> _type) 
		{ 
			m_Type = _type; 
			RefreshRootName();
		};
		std::string TagComponent::GetTypeName() { return std::get<0>(m_Type); }
		std::string TagComponent::GetTypeIcon() { return std::get<1>(m_Type); };
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