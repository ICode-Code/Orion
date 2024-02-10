#include "IVFlatMaterialMeshRenderer.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVFlatMaterialMeshRenderer::~IVFlatMaterialMeshRenderer()
		{

		}

		void IVFlatMaterialMeshRenderer::Render(Core::IVCoreDrawDataBuffer& _data, int _camera_idx)
		{
			for (auto iter = _data.begin(); iter != _data.end(); iter++)
			{
				Core::IVCoreDrawPackage& _draw_pkg = iter->second;
				_draw_pkg.SHADER->Attach();
				_draw_pkg.SHADER->Set1i("ActiveCameraIndex", _camera_idx);
				for (size_t i = 0; i < _draw_pkg.MESH_LIST.size(); i++)
				{
					if (!_draw_pkg.MESH_LIST[i]->DrawCount)
						continue;

					_draw_pkg.MESH_LIST[i]->Material->Attach();
					glBindVertexArray(_draw_pkg.MESH_LIST[i]->VAO);
					glDrawElementsInstanced(GL_TRIANGLES, _draw_pkg.MESH_LIST[i]->IndiceCount, GL_UNSIGNED_INT, 0, _draw_pkg.MESH_LIST[i]->DrawCount);

				}
			}
		}
	}
}