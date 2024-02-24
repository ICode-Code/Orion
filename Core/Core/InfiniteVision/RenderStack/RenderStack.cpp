#include "RenderStack.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRenderStack::~IVRenderStack()
		{

		}
		void IVRenderStack::RegisterCoreStaticMesh(Core::IVCoreDrawStaticMeshDataBuffer& _buffer, CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			if (_buffer.find(_mesh_id) == _buffer.end())
			{
				Core::IVCoreDrawStaticMeshPackage _draw_pkg;
				_draw_pkg.MATERIAL_ID = _mesh->Material->GetOffset();
				_draw_pkg.MESH_LIST = std::vector<CoreMeshInstanceRenderDescriptor*>();
				_draw_pkg.SHADER = _mesh->Material->GetShader();
				_draw_pkg.MESH_ID = _mesh_id;
				_buffer.insert(std::make_pair(_mesh_id, _draw_pkg));
			}

			_buffer[_mesh_id].MESH_LIST.push_back(_mesh);
		}
		void IVRenderStack::RegisterCoreDynamicMesh(Core::IVCoreDrawDynamicMeshDataBuffer& _buffer, CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			if (_buffer.find(_mesh_id) == _buffer.end())
			{
				Core::IVCoreDrawDynamicMeshPackage _draw_pkg;
				_draw_pkg.MATERIAL_ID = _mesh->Material->GetOffset();
				_draw_pkg.MESH_LIST = std::vector<CoreMeshInstanceRenderDescriptor*>();
				_draw_pkg.SHADER = _mesh->Material->GetShader();
				_draw_pkg.MESH_ID = _mesh_id;
				_buffer.insert(std::make_pair(_mesh_id, _draw_pkg));
			}

			_buffer[_mesh_id].MESH_LIST.push_back(_mesh);
		}

		void IVRenderStack::RegisterOpaqueStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreStaticMesh(m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterTransparentStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreStaticMesh(m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterFlatMaterialStaticMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreStaticMesh(m_STATIC_MESH_FLAT_MATERIAL_BUFFER, _mesh, _mesh_id);
		}

		void IVRenderStack::RegisterOpaqueSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreDynamicMesh(m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterTransparentSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreDynamicMesh(m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh, _mesh_id);
		}
		void IVRenderStack::RegisterFlatMaterialSkinnedMesh(CoreMeshInstanceRenderDescriptor* _mesh, uint32_t _mesh_id)
		{
			RegisterCoreDynamicMesh(m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER, _mesh, _mesh_id);
		}

		void IVRenderStack::PurgeFromStack(uint32_t _id)
		{
			this->PurgeFromStaticMeshList(m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER, _id);
			this->PurgeFromStaticMeshList(m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _id);
			this->PurgeFromStaticMeshList(m_STATIC_MESH_FLAT_MATERIAL_BUFFER, _id);

			this->PurgeFromDynamicMeshList(m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER, _id);
			this->PurgeFromDynamicMeshList(m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _id);
			this->PurgeFromDynamicMeshList(m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER, _id);
		}
		std::vector<CoreMeshInstanceRenderDescriptor*> IVRenderStack::QueryLWStaticMeshByMaterial(uint32_t _material_id, bool _clear_existing)
		{
			std::vector<CoreMeshInstanceRenderDescriptor*> _mesh_frag_buffer;

			if (_clear_existing)
			{
				ClearCollectLWStaticMeshByMaterial(m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				ClearCollectLWStaticMeshByMaterial(m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				ClearCollectLWStaticMeshByMaterial(m_STATIC_MESH_FLAT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
			}
			else
			{
				CollectLWStaticMeshByMaterial(m_STATIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				CollectLWStaticMeshByMaterial(m_STATIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				CollectLWStaticMeshByMaterial(m_STATIC_MESH_FLAT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
			}

			return _mesh_frag_buffer;

		}
		std::vector<CoreMeshInstanceRenderDescriptor*> IVRenderStack::QueryLWDynamicMeshByMaterial(uint32_t _material_id, bool _clear_existing)
		{
			std::vector<CoreMeshInstanceRenderDescriptor*> _mesh_frag_buffer;

			if (_clear_existing)
			{
				ClearCollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				ClearCollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				ClearCollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
			}
			else
			{
				CollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_OPAQUE_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				CollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_TRANSPARENT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
				CollectLWDynamicMeshByMaterial(m_DYNAMIC_MESH_FLAT_MATERIAL_BUFFER, _mesh_frag_buffer, _material_id);
			}

			return _mesh_frag_buffer;
		}
		void IVRenderStack::CollectLWStaticMeshByMaterial(Core::IVCoreDrawStaticMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id)
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
		void IVRenderStack::ClearCollectLWStaticMeshByMaterial(Core::IVCoreDrawStaticMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id)
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
		void IVRenderStack::PurgeFromStaticMeshList(Core::IVCoreDrawStaticMeshDataBuffer& buffer, uint32_t _mesh_id)
		{
			if (buffer.find(_mesh_id) != buffer.end())
			{
				auto& instance = buffer[_mesh_id];

				std::vector<CoreMeshInstanceRenderDescriptor*> _filtered_list;

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


		void IVRenderStack::CollectLWDynamicMeshByMaterial(Core::IVCoreDrawDynamicMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id)
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
		void IVRenderStack::ClearCollectLWDynamicMeshByMaterial(Core::IVCoreDrawDynamicMeshDataBuffer& _mem, std::vector<CoreMeshInstanceRenderDescriptor*>& _buffer, uint32_t _material_id)
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
			if (_safe_to_purge)
				_mem.erase(_purge_mesh_id);
		}

		void IVRenderStack::PurgeFromDynamicMeshList(Core::IVCoreDrawDynamicMeshDataBuffer& buffer, uint32_t _mesh_id)
		{
			if (buffer.find(_mesh_id) != buffer.end())
			{
				auto& instance = buffer[_mesh_id];

				std::vector<CoreMeshInstanceRenderDescriptor*> _filtered_list;

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