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


		void TurboOT::Register(Entity _entity)
		{
			Component::CoreRenderableMeshComponent* _core_mesh_component = nullptr;

			
			if (_entity.HasComponent<Component::MeshComponent>())
				_core_mesh_component = &_entity.GetComponent<Component::MeshComponent>();
			else if (_entity.HasComponent<Component::SkinnedMeshComponent>())
				_core_mesh_component = &_entity.GetComponent<Component::SkinnedMeshComponent>();

			if (!_core_mesh_component)
			{
				LOG_ERROR("Invalid entity to store in TurboOT");
				return;
			}

			OTEntDiscriptor __discriptor;
			
			Component::TransformComponent& __transform = _entity.GetComponent<Component::TransformComponent>();
			IVModel* _core_model = AssetManager::GetGeometry(_core_mesh_component->GetPackageID());

			__discriptor.EntityID = (uint32_t)_entity;
			__discriptor.Bound = _core_model->Bound;

			__discriptor.UpdateBuffer = std::bind(&Component::CoreRenderableMeshComponent::UpdateBuffers, _core_mesh_component);
			__discriptor.UpdateOffset = std::bind(&Component::CoreRenderableMeshComponent::SetOffset, _core_mesh_component, std::placeholders::_1);
			__discriptor.Position = __transform.m_Position;
			__discriptor.Valid = true;

			m_RootNode.RegisterChild(__discriptor);

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
	}
}