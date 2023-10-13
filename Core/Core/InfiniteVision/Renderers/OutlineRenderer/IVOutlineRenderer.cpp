#include "IVOutlineRenderer.h"
#include "../../../ActiveEntity/ActiveEntity.h"

namespace OE1Core
{
	namespace Renderer
	{
		IVOutlineRenderer::IVOutlineRenderer()
		{
			m_Shader = ShaderManager::GetShader(ShaderID::OBJECT_OUTLINE);
		}
		IVOutlineRenderer::~IVOutlineRenderer()
		{

		}

		void IVOutlineRenderer::Render(ActiveEntity* _active_entity)
		{
			if (!_active_entity->ValidSelection())
				return;
		
			if (!ValidEntityToOutline(_active_entity->GetActive().GetComponent<Component::TagComponent>().GetType()))
				return;

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);


			for (size_t i = 0; i < _active_entity->GetRegistry().size(); i++)
				IssueProxyRender(_active_entity->GetRegistry()[i]);

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);

			m_Shader->Attach();
			for (size_t i = 0; i < _active_entity->GetRegistry().size(); i++)
				IssueSolidOutLineRender(_active_entity->GetRegistry()[i]);
			m_Shader->Detach();

			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}

		void IVOutlineRenderer::IssueProxyRender(Entity _entity)
		{
			Component::TagComponent& tag = _entity.GetComponent<Component::TagComponent>();

			Component::MeshComponent& mesh = _entity.GetComponent<Component::MeshComponent>();
			ModelPkg* model = AssetManager::GetGeometry(mesh.GetPackageID());

			Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();


			glm::mat4 world_transform = transform.QueryWorldTransform();

			for (size_t i = 0; i < model->MeshList.size(); i++)
			{
				model->MeshList[i].Material->GetShader()->AttachProxy();
				model->MeshList[i].Material->GetShader()->SetProxyMat4("Model", world_transform);
				model->MeshList[i].Material->Attach();

				glBindVertexArray(model->MeshList[i].VAO);

				glDrawElements(GL_TRIANGLES, model->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);


				model->MeshList[i].Material->GetShader()->Detach();
			}
		}
		void IVOutlineRenderer::IssueSolidOutLineRender(Entity _entity)
		{
			Component::MeshComponent& mesh = _entity.GetComponent<Component::MeshComponent>();
			ModelPkg* model = AssetManager::GetGeometry(mesh.GetPackageID());

			Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
			glm::mat4 world_transform = transform.QueryWorldTransform();

			m_Shader->SetMat4("Model", world_transform);
			for (size_t i = 0; i < model->MeshList.size(); i++)
			{
				glBindVertexArray(model->MeshList[i].VAO);
				glDrawElements(GL_TRIANGLES, model->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);
			}
		}

		bool IVOutlineRenderer::ValidEntityToOutline(EntityType _type)
		{
			
			return 
			(_type != EntityType::T_WRAPPER)	&&
			(_type != EntityType::T_EMPTY)		&&
			(_type != EntityType::T_CAMERA);
		}
	}
}