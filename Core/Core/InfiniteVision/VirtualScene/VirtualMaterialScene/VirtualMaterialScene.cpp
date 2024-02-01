#include "VirtualMaterialScene.h"
#include "../../../Material/MasterMaterial.h"
#include "../../AssetManager/AssetManager.h"

namespace OE1Core
{
	VirtualMaterialScene::VirtualMaterialScene(SDL_Window* _win)
		: VirtualScene{ _win }
	{
		m_VirtualRenderMesh = AssetManager::GetGeometryI(DynamicAssetType::SPHERE);
	}
	VirtualMaterialScene::~VirtualMaterialScene()
	{

	}

	void VirtualMaterialScene::Render(MasterMaterial* _material)
	{
		m_VirtualMaterialSceneFramebuffer = new Renderer::IVVirtualMaterialSceneFramebuffer(
			_material->GetPreviewRef()
		);

		m_VirtualMaterialSceneFramebuffer->Attach();
		glViewport(0, 0, m_VirtualMaterialSceneFramebuffer->GetWidth(), m_VirtualMaterialSceneFramebuffer->GetHeight());
		
		_material->GetShader()->Attach();
		_material->Attach();
		for (size_t i = 0; i < m_VirtualRenderMesh->MeshList.size(); i++)
		{
			glBindVertexArray(m_VirtualRenderMesh->MeshList[i].VAO);
			glDrawElements(GL_TRIANGLE_STRIP, m_VirtualRenderMesh->MeshList[i].IndiceCount, GL_UNSIGNED_INT, 0);
		}





		
	}
}