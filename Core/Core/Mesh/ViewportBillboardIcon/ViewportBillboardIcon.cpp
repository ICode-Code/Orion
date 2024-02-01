#include "ViewportBillboardIcon.h"
#include "../../Component/ViewportBillboardComponent/ViewportBillboardComponent.h"
#include "../../Scene/Scene.h"
#include "LogUI.h"

namespace OE1Core
{
	ViewportBillboardIcon::ViewportBillboardIcon(Texture* _texture)
	{
		m_Texture = _texture;
		m_BaseQuad = new BaseQuad();
		Init();
	}
	ViewportBillboardIcon::ViewportBillboardIcon(ViewportBillboardIcon& _other)
	{
		*this = _other;
	}
	ViewportBillboardIcon::~ViewportBillboardIcon()
	{
		delete m_BaseQuad;
	}


	const Texture* ViewportBillboardIcon::GetTexture() const
	{
		return m_Texture;
	}
	const BaseQuad* ViewportBillboardIcon::GetBaseQuad() const
	{
		return m_BaseQuad;
	}
	int ViewportBillboardIcon::GetInstanceCount() const 
	{
		return m_ActiveInstanceCount;
	}
	int ViewportBillboardIcon::AddInstance(uint32_t _instanceID)
	{
		for (size_t i = 0; i < m_InstanceIDs.size(); i++)
			if (m_InstanceIDs[i] == _instanceID)
				return -1;

		m_InstanceIDs.push_back(_instanceID);
		m_ActiveInstanceCount++;
		return (int)m_InstanceIDs.size() - 1;
	}
	bool ViewportBillboardIcon::PurgeInstance(uint32_t _instance_id, Scene* _scene)
	{
		int erase_idx = -1;
		for (size_t i = 0; i < m_InstanceIDs.size(); i++)
		{
			if (m_InstanceIDs[i] == _instance_id)
			{
				erase_idx = (int)i;
				break;
			}
		}

		if (erase_idx == -1)
		{
			LOG_ERROR(LogLayer::Pipe("Cannot delete non-existing Billboard Icon", OELog::CRITICAL));
			return false;
		}

		m_InstanceIDs.erase(m_InstanceIDs.begin() + erase_idx);
		m_ActiveInstanceCount--;

		// Update component buffer offset
		for (size_t i = 0; i < m_InstanceIDs.size(); i++)
		{
			Entity _entity = Entity((entt::entity)m_InstanceIDs[i], _scene);
			if (_entity.HasComponent<Component::ViewportBillboardComponent>())
			{
				Component::ViewportBillboardComponent& _billboard_component = _entity.GetComponent<Component::ViewportBillboardComponent>();
				_billboard_component.UpdateOffset((GLintptr)i);
			}
			else
			{
				LOG_ERROR(LogLayer::Pipe("Failed To Update Billboard Icon Buffer! Component Not-Found!", OELog::WARNING));
			}
			
		}

		return true;
	}
	void ViewportBillboardIcon::Init()
	{
		glGenVertexArrays(1, &m_BaseQuad->m_VAO);
		glBindVertexArray(m_BaseQuad->m_VAO);

		glGenBuffers(1, &m_BaseQuad->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_BaseQuad->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_BaseQuad->m_QuadVertexData), &m_BaseQuad->m_QuadVertexData, GL_STATIC_DRAW);

		glGenBuffers(1, &m_BaseQuad->m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BaseQuad->m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_BaseQuad->m_Indices), &m_BaseQuad->m_Indices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

		// Instance
		glGenBuffers(1, &m_BaseQuad->m_InstanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_BaseQuad->m_InstanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, ViewportBillboardInstancePkgSize * m_InitialInstanceBufferSize, NULL, GL_DYNAMIC_DRAW);

		// Transform Materix
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, ViewportBillboardInstancePkgSize, (void*)0);
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, ViewportBillboardInstancePkgSize, (void*)(sizeof(glm::vec4)));
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, ViewportBillboardInstancePkgSize, (void*)(2 * sizeof(glm::vec4)));
		glEnableVertexAttribArray(5);
		glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, ViewportBillboardInstancePkgSize, (void*)(3 * sizeof(glm::vec4)));

		glEnableVertexAttribArray(6);
		glVertexAttribIPointer(6, 1, GL_INT, ViewportBillboardInstancePkgSize, (void*)offsetof(ViewportBillboardInstancePkg, ViewportBillboardInstancePkg::ID));

		
		// Once per instance

		glVertexAttribDivisor(2, 1);//
		glVertexAttribDivisor(3, 1);// Transform
		glVertexAttribDivisor(4, 1);//
		glVertexAttribDivisor(5, 1);//


		glVertexAttribDivisor(6, 1); // Instance ID

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);


	}
}