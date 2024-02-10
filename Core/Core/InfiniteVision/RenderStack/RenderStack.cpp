#include "RenderStack.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRenderStack::~IVRenderStack()
		{

		}
		void IVRenderStack::RegisterCoreMesh(Core::IVCoreDrawDataBuffer& _buffer, lwStaticMeshPkg* _mesh, uint32_t _mesh_id)
		{
			if (_buffer.find(_mesh_id) == _buffer.end())
			{
				Core::IVCoreDrawPackage _draw_pkg;
				_draw_pkg.MATERIAL_ID = _mesh->Material->GetOffset();
				_draw_pkg.MESH_LIST = std::vector<lwStaticMeshPkg*>();
				_draw_pkg.SHADER = _mesh->Material->GetShader();
				_draw_pkg.MESH_ID = _mesh_id;
				_buffer.insert(std::make_pair(_mesh_id, _draw_pkg));
			}

			_buffer[_mesh_id].MESH_LIST.push_back(_mesh);
		}
		void IVRenderStack::RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreMesh(s_OpaqueMeshList, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterTransparentMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreMesh(s_TransparentMeshList, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterFlatMaterialMesh(lwStaticMeshPkg* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreMesh(s_FlatMaterialMeshList, _mesh, _mesh_id);
		}
		void IVRenderStack::PurgeFromStack(uint32_t _id)
		{
			this->PurgeFromMeshList(s_OpaqueMeshList, _id);
			this->PurgeFromMeshList(s_TransparentMeshList, _id);
			this->PurgeFromMeshList(s_FlatMaterialMeshList, _id);
		}
		std::vector<lwStaticMeshPkg*> IVRenderStack::QueryLWStaticMeshByMaterial(uint32_t _material_id, bool _clear_existing)
		{
			std::vector<lwStaticMeshPkg*> _mesh_frag_buffer;

			if (_clear_existing)
			{
				ClearCollectLWMeshByMaterial(s_OpaqueMeshList, _mesh_frag_buffer, _material_id);
				ClearCollectLWMeshByMaterial(s_TransparentMeshList, _mesh_frag_buffer, _material_id);
				ClearCollectLWMeshByMaterial(s_FlatMaterialMeshList, _mesh_frag_buffer, _material_id);
			}
			else
			{
				CollectLWMeshByMaterial(s_OpaqueMeshList, _mesh_frag_buffer, _material_id);
				CollectLWMeshByMaterial(s_TransparentMeshList, _mesh_frag_buffer, _material_id);
				CollectLWMeshByMaterial(s_FlatMaterialMeshList, _mesh_frag_buffer, _material_id);
			}

			return _mesh_frag_buffer;

		}
		void IVRenderStack::CollectLWMeshByMaterial(Core::IVCoreDrawDataBuffer& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _material_id)
		{
			for (auto iter = _mem.begin(); iter != _mem.end(); iter++)
			{
				if (iter->second.MATERIAL_ID == _material_id)
				{
					// We assume all the list in one buffer share  the material
					_buffer = iter->second.MESH_LIST;
					// We also assume this material id is unique so it is safe to break here
					break;
				}
			}
		}
		void IVRenderStack::ClearCollectLWMeshByMaterial(Core::IVCoreDrawDataBuffer& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _material_id)
		{
			uint32_t _purge_mesh_id;
			bool _safe_to_purge = false;
			for (auto iter = _mem.begin(); iter != _mem.end(); iter++)
			{
				if (iter->second.MATERIAL_ID == _material_id)
				{
					// We assume all the list in one buffer share  the material
					_buffer = iter->second.MESH_LIST;
					_purge_mesh_id = iter->second.MESH_ID;
					_safe_to_purge = true;
					// We also assume this material id is unique so it is safe to break here
					break;
				}
			}

			// Since it is ClearCollect: WE PURGE
			if(_safe_to_purge)
				_mem.erase(_purge_mesh_id);
		}
		void IVRenderStack::PurgeFromMeshList(Core::IVCoreDrawDataBuffer& buffer, uint32_t _mesh_id)
		{
			if (buffer.find(_mesh_id) != buffer.end())
			{
				auto& instance = buffer[_mesh_id];

				std::vector<lwStaticMeshPkg*> _filtered_list;

				for (size_t i = 0; i < instance.MESH_LIST.size(); i++)
				{
					//instance.second[i]->DrawCount--;
					if (instance.MESH_LIST[i]->DrawCount > 0)
						_filtered_list.push_back(instance.MESH_LIST[i]);
				}

				if (_filtered_list.empty())
				{
					// If all instance in count is 0
					buffer.erase(_mesh_id); // remove from the draw list
				}
				else
				{
					// Update the list
					buffer[_mesh_id].MESH_LIST = _filtered_list;
				}
			}
		}
	}
}