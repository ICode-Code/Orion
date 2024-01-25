#include "RenderStack.h"


namespace OE1Core
{
	namespace Renderer
	{
		IVRenderStack::~IVRenderStack()
		{

		}


		void IVRenderStack::RegisterOpaqueMesh(lwStaticMeshPkg* _mesh, uint32_t _id)
		{
			if (s_OpaqueMeshList.find(_id) == s_OpaqueMeshList.end())
				s_OpaqueMeshList.insert(std::make_pair(_id, std::make_pair(_mesh->Material->GetShader(), std::vector<lwStaticMeshPkg*>())));

			std::get<1>(s_OpaqueMeshList[_id]).push_back(_mesh);
		}
		void IVRenderStack::RegisterTransparentMesh(lwStaticMeshPkg* _mesh, uint32_t _id)
		{
			if (s_TransparentMeshList.find(_id) == s_TransparentMeshList.end())
				s_TransparentMeshList.insert(std::make_pair(_id, std::make_pair(_mesh->Material->GetShader(), std::vector<lwStaticMeshPkg*>())));

			std::get<1>(s_TransparentMeshList[_id]).push_back(_mesh);
		}
		void IVRenderStack::RegisterFlatMaterialMesh(lwStaticMeshPkg* _mesh, uint32_t _id)
		{

			if (s_FlatMaterialMeshList.find(_id) == s_FlatMaterialMeshList.end())
				s_FlatMaterialMeshList.insert(std::make_pair(_id, std::make_pair(_mesh->Material->GetShader(), std::vector<lwStaticMeshPkg*>())));

			std::get<1>(s_FlatMaterialMeshList[_id]).push_back(_mesh);
		}
		void IVRenderStack::PurgeFromStack(uint32_t _id)
		{
			this->PurgeFromMeshList(s_OpaqueMeshList, _id);
			this->PurgeFromMeshList(s_TransparentMeshList, _id);
			this->PurgeFromMeshList(s_FlatMaterialMeshList, _id);
		}
		std::vector<lwStaticMeshPkg*> IVRenderStack::QueryLWStaticMesh(uint32_t _id, bool _clear_existing)
		{

			std::vector<lwStaticMeshPkg*> _mesh_frag_buffer;

			if (_clear_existing)
			{
				ClearCollectLWMesh(s_OpaqueMeshList, _mesh_frag_buffer, _id);
				ClearCollectLWMesh(s_TransparentMeshList, _mesh_frag_buffer, _id);
				ClearCollectLWMesh(s_FlatMaterialMeshList, _mesh_frag_buffer, _id);
			}
			else
			{
				CollectLWMesh(s_OpaqueMeshList, _mesh_frag_buffer, _id);
				CollectLWMesh(s_TransparentMeshList, _mesh_frag_buffer, _id);
				CollectLWMesh(s_FlatMaterialMeshList, _mesh_frag_buffer, _id);
			}

			return _mesh_frag_buffer;

		}
		void IVRenderStack::CollectLWMesh(IVRenderStack::IVDrawData& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _id)
		{
			if (_mem.find(_id) != _mem.end())
			{
				for (size_t i = 0; i < _mem[_id].second.size(); i++)
					_buffer.push_back(_mem[_id].second[i]);
			}
		}
		void IVRenderStack::ClearCollectLWMesh(IVRenderStack::IVDrawData& _mem, std::vector<lwStaticMeshPkg*>& _buffer, uint32_t _id)
		{
			if (_mem.find(_id) != _mem.end())
			{
				for (size_t i = 0; i < _mem[_id].second.size(); i++)
					_buffer.push_back(_mem[_id].second[i]);

				_mem[_id].second.clear();
				_mem.erase(_id);
			}
		}
		void IVRenderStack::PurgeFromMeshList(IVRenderStack::IVDrawData& buffer, uint32_t _id)
		{
			if (buffer.find(_id) != buffer.end())
			{
				auto& instance = buffer[_id];

				std::vector<lwStaticMeshPkg*> _filtered_list;

				for (size_t i = 0; i < instance.second.size(); i++)
				{
					//instance.second[i]->DrawCount--;
					if (instance.second[i]->DrawCount > 0)
						_filtered_list.push_back(instance.second[i]); 
				}

				if (_filtered_list.empty())
				{
					// If all instance in count is 0
					buffer.erase(_id); // remove from the draw list
				}
				else
				{
					// Update the list
					buffer[_id].second = _filtered_list;
				}
			}
		}
	}
}