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

		void IVOutlineRenderer::Render(ActiveEntity _active_entity)
		{
			if (!_active_entity.ValidSelection())
				return;

			Entity active_entity = _active_entity.GetActive();
			Component::MeshComponent& mesh = active_entity.GetComponent<Component::MeshComponent>();
			Component::TransformComponent& transform = active_entity.GetComponent<Component::TransformComponent>();
			
			ModelPkg* model = AssetManager::GetGeometry(mesh.GetPackageID());

			glStencilFunc(GL_ALWAYS, 1, 0xFF);
			glStencilMask(0xFF);


			glm::mat4 world_transform = transform.GetWorldTransform();

			for (size_t i = 0; i < model->MeshList.size(); i++)
			{
				model->MeshList[i].Material->GetShader()->AttachProxy();
				model->MeshList[i].Material->GetShader()->SetProxyMat4("Model", world_transform);
				model->MeshList[i].Material->Attach();

				glBindVertexArray(model->MeshList[i].VAO);

				glDrawElements(GL_TRIANGLES, model->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);


				model->MeshList[i].Material->GetShader()->Detach();
			}

			glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
			glStencilMask(0x00);
			glDisable(GL_DEPTH_TEST);

			m_Shader->Attach();
			m_Shader->SetMat4("Model", world_transform);
			for (size_t i = 0; i < model->MeshList.size(); i++)
			{
				glBindVertexArray(model->MeshList[i].VAO);
				glDrawElements(GL_TRIANGLES, model->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);
			}
			m_Shader->Detach();

			glStencilMask(0xFF);
			glStencilFunc(GL_ALWAYS, 0, 0xFF);
			glEnable(GL_DEPTH_TEST);
		}
	}
}