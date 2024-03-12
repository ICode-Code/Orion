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

		void IVOutlineRenderer::Render(ActiveEntity* _active_entity, int _camera_idx)
		{
			if (!_active_entity->ValidSelection())
				return;
		
			if (!ValidEntityToOutline(_active_entity->GetActive().GetComponent<Component::TagComponent>().GetType()))
				return;

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);


			for (size_t i = 0; i < _active_entity->GetRegistry().size(); i++)
				IssueProxyRender(_active_entity->GetRegistry()[i], _camera_idx);

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);

			m_Shader->Attach();
			m_Shader->Set1i("ActiveCameraIndex", _camera_idx);
			for (size_t i = 0; i < _active_entity->GetRegistry().size(); i++)
				IssueSolidOutLineRender(_active_entity->GetRegistry()[i], _camera_idx);
			m_Shader->Detach();

			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}

		void IVOutlineRenderer::IssueProxyRender(Entity _entity, int _camera_idx)
		{
			Component::TagComponent& tag = _entity.GetComponent<Component::TagComponent>();
			
			Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
			glm::mat4 world_transform = transform.QueryWorldTransform();


			IVModel* model = GetRenderbaleModel(_entity);

			if (model)
			{
				for (size_t i = 0; i < model->SubMeshs.size(); i++)
				{
					model->SubMeshs[i].Material->GetShader()->AttachProxy();
					model->SubMeshs[i].Material->GetShader()->SetProxyMat4("Model", world_transform);
					model->SubMeshs[i].Material->Attach();

					glBindVertexArray(model->SubMeshs[i].VAO);

					glDrawElements(GL_TRIANGLES, model->SubMeshs[i].IndicesCount, GL_UNSIGNED_INT, 0);


					model->SubMeshs[i].Material->GetShader()->Detach();
				}
			}
			
		}
		void IVOutlineRenderer::IssueSolidOutLineRender(Entity _entity, int _camera_idx)
		{
			

			Component::TransformComponent& transform = _entity.GetComponent<Component::TransformComponent>();
			glm::mat4 world_transform = transform.QueryWorldTransform();

			IVModel* model = GetRenderbaleModel(_entity);

			if (model)
			{
				m_Shader->Set1i("hasAnimation", (model->Type == CoreMeshDescriptor::CoreMeshType::DYNAMIC));
				m_Shader->SetMat4("Model", world_transform);
				for (size_t i = 0; i < model->SubMeshs.size(); i++)
				{
					glBindVertexArray(model->SubMeshs[i].VAO);
					glDrawElements(GL_TRIANGLES, model->SubMeshs[i].IndicesCount, GL_UNSIGNED_INT, 0);
				}
			}
			
		}
		IVModel* IVOutlineRenderer::GetRenderbaleModel(Entity _entity)
		{
			IVModel* __model = nullptr;

			if (_entity.HasComponent<Component::MeshComponent>())
			{
				Component::MeshComponent& mesh = _entity.GetComponent<Component::MeshComponent>();
				__model = AssetManager::GetGeometry(mesh.GetPackageID());
			}
			else if (_entity.HasComponent<Component::SkinnedMeshComponent>())
			{
				Component::SkinnedMeshComponent& mesh = _entity.GetComponent<Component::SkinnedMeshComponent>();
				__model = AssetManager::GetGeometry(mesh.GetPackageID());
			}

			return __model;
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