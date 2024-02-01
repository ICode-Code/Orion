#include "ViewportBillboardComponent.h"
#include "../../Mesh/ViewportBillboardIcon/ViewportBillboardIcon.h"
#include "LogUI.h"
namespace OE1Core
{
	namespace Component
	{

		ViewportBillboardComponent::ViewportBillboardComponent(ViewportBillboardIcon* _sprite, uint32_t _entity_id, ViewportIconBillboardType _type)
		{
			m_Type = _type;
			m_Sprite = _sprite;
			m_EntityID = _entity_id;
			m_MemoryOffset = m_Sprite->AddInstance(m_EntityID);
			m_InstanceBufferID = m_Sprite->GetBaseQuad()->m_InstanceBuffer;

			UpdateOffset(m_MemoryOffset);
		}
		ViewportBillboardComponent::ViewportBillboardComponent(ViewportBillboardComponent& other, uint32_t _entity_id)
		{
			m_Type = other.m_Type;
			m_EntityID = _entity_id;
			m_Sprite = other.m_Sprite;
			m_MemoryOffset = m_Sprite->AddInstance(m_EntityID);
			m_InstanceBufferID = m_Sprite->GetBaseQuad()->m_InstanceBuffer;

			UpdateOffset(m_MemoryOffset);
		}
		ViewportBillboardComponent::~ViewportBillboardComponent()
		{

		}


		uint32_t ViewportBillboardComponent::GetEntityID() const { return m_EntityID; }
		GLuint ViewportBillboardComponent::GetInstanceBufferID() const { return m_InstanceBufferID; }
		GLintptr ViewportBillboardComponent::GetMemoryOffset() const { return m_MemoryOffset; }
		ViewportBillboardInstancePkg ViewportBillboardComponent::GetInstanceData() const { return m_InstanceData; }



		void ViewportBillboardComponent::UpdateOffset(const GLintptr _offset)
		{
			m_MemoryOffset = _offset * ViewportBillboardInstancePkgSize;
			glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferID);
			glBufferSubData(GL_ARRAY_BUFFER, m_MemoryOffset, ViewportBillboardInstancePkgSize, &m_InstanceData);
		}
		void ViewportBillboardComponent::Update(glm::mat4& _transform, glm::mat4& _camera_view)
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_InstanceBufferID);
			m_InstanceData.Transform = FaceCamera(_camera_view * _transform);
			m_InstanceData.ID = m_EntityID;
			glBufferSubData(GL_ARRAY_BUFFER, m_MemoryOffset, ViewportBillboardInstancePkgSize, &m_InstanceData);
		}
		ViewportIconBillboardType ViewportBillboardComponent::GetType()  const
		{
			return m_Type;
		}
		glm::mat4 ViewportBillboardComponent::FaceCamera(glm::mat4 _view_model)
		{
			_view_model[0] = glm::vec4(m_Scale, 0.0f, 0.0f, _view_model[0][3]);
			_view_model[1] = glm::vec4(0.0f, m_Scale, 0.0f, _view_model[1][3]);
			_view_model[2] = glm::vec4(0.0f, 0.0f, m_Scale, _view_model[2][3]);

			return _view_model;
		}

		void ViewportBillboardComponent::SetScale(float _scale)
		{
			if (_scale < 0.01f || _scale > 2.0f)
			{
				LOG_ERROR(LogLayer::Pipe("Invalid Scale to apply billoard!", OELog::CRITICAL));
				return;
			}
			m_Scale = _scale;
		}
		float ViewportBillboardComponent::GetScale() const { return m_Scale; }

		void ViewportBillboardComponent::SetEntityID(uint32_t _id)
		{
			m_EntityID = _id;
		}
		bool ViewportBillboardComponent::IsReady() const
		{
			return m_Ready;
		}
	}
}