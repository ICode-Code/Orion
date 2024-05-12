#include "TurboOT.h"
#include "../Core/Scene/Entity.h"
#include "LogUI.h"

namespace OE1Core
{
	namespace DS
	{
		TurboOT::TurboOT()
			: m_RootNode{glm::vec3(0.0f), 1.0f, 0, true}
		{
			
		}
		TurboOT::~TurboOT()
		{

		}
		void TurboOT::FrustumCull(std::map<uint64_t, Component::CameraComponent*>& _cameras)
		{
			/*m_CulledBuffer.clear();
			for (auto iter = _cameras.begin(); iter != _cameras.end(); iter++)
			{
				if (iter->second.Camera->GetCamera()->ShouldCull())
				{
					m_RootNode.Filter(iter->second.Camera->GetCamera()->GetFrustum(), m_CulledBuffer);
				}
				break;
			}*/
		}

		void TurboOT::Register(OTEntDiscriptor _discriptor)
		{
			m_RootNode.RegisterChild(_discriptor);

		}
		void TurboOT::Update(Entity _entity)
		{
			// Query Data
			OTEntDiscriptor __dis = m_RootNode.GetData((uint32_t)_entity);
			if (__dis.Valid)
			{
				// Remove the existing one
				if(m_RootNode.PurgeChild((uint32_t)_entity)) 
				{
					// if the purge is succesful 
					// update position
					Component::TransformComponent& _transform = _entity.GetComponent<Component::TransformComponent>();
					__dis.Position = _transform.m_Position;

					m_RootNode.RegisterChild(__dis);
				}
				else
				{
					LogLayer::Pipe("Failed to delete entity, inside <TurboOT>", OELog::CRITICAL);
				}
			}
			else
			{
				LogLayer::Pipe("Entity Query to <TurboOT> was unsuccessfull!", OELog::CRITICAL);
			}
		}
		void TurboOT::Purge(Entity _entity)
		{

		}
		TurboOTNode& TurboOT::GetRootNode() { return m_RootNode; }
		std::unordered_map<uint32_t, std::vector<OTEntDiscriptor>>& TurboOT::GetCulledBuffer() { return m_CulledBuffer; };
	}
}