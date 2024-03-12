#include "UniformBlockManager.h"

#define ORI_MAX_ANIMATION_UNIFORM_BUFFER 1
namespace OE1Core
{
	namespace Memory
	{
		UniformBlockManager::UniformBlockManager(ShaderInterface* _shader_interface)
		{
			s_ShaderInterface =  _shader_interface;
			RegisterUniformBuffers();
			LinkUniformBuffers();
			

			s_SceneTransformBuffer = &s_UniformBuffers[Memory::UniformBufferID::SCENE_TRANSFORM];
		}
		UniformBlockManager::~UniformBlockManager()
		{
			for (auto& iter : s_UniformBuffers)
				glDeleteBuffers(1, &iter.second.Buffer);
		}
		Memory::UniformBuffer* UniformBlockManager::GetBuffer(Memory::UniformBufferID _id)
		{
			if (s_UniformBuffers.find(_id) == s_UniformBuffers.end())
				return nullptr;
			return &s_UniformBuffers[_id];
		}
		Memory::UniformBuffer* UniformBlockManager::GetBuffer(Memory::UniformBufferIDArray _id, int _idx)
		{
			if (s_UniformBuffersArray.find(_id) == s_UniformBuffersArray.end())
				return nullptr;

			return &s_UniformBuffersArray[_id][_idx];
		}
		std::vector<Memory::UniformBuffer>& UniformBlockManager::GetBuffers(Memory::UniformBufferIDArray _id)
		{
			assert(s_UniformBuffersArray.find(_id) != s_UniformBuffersArray.end());

			return s_UniformBuffersArray[_id];
		}
		Memory::UniformBuffer* UniformBlockManager::UseBuffer(Memory::UniformBufferID _id)
		{
			return &s_UniformBuffers[_id];
		}
		void UniformBlockManager::RegisterUniformBuffers()
		{
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::INFIN_GRID,				Memory::UniformBuffer("InfiniteGrid")));
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::SCENE_TRANSFORM,		Memory::UniformBuffer("SceneCameraTransform")));
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::MATERIAL_REGISTRY,		Memory::UniformBuffer("MaterialProperties")));
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::TAI_REGISTRY,			Memory::UniformBuffer("TextureAccessIndex")));
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::ANIMATION_REGISTRY,		Memory::UniformBuffer("AnimationBuffer")));

			//// Init Array for Animation buffer
			//std::vector<Memory::UniformBuffer> _buffers;
			//for (int i = 0; i < ORI_MAX_ANIMATION_UNIFORM_BUFFER; i++)
			//	_buffers.push_back(Memory::UniformBuffer("AnimationBuffer"));
			//s_UniformBuffersArray.insert(std::make_pair(Memory::UniformBufferIDArray::ANIMATION_REGISTRY_ARRAY, _buffers));

			
		}
		void UniformBlockManager::LinkUniformBuffers()
		{
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::INFIN_GRID],			Memory::s_InfiniteGridBufferSize,	1);
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::SCENE_TRANSFORM],		Memory::s_SceneTransformBufferSize, ORI_MAX_SCENE_CAMERA);

			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::MATERIAL_REGISTRY],	Memory::s_MaterialPropertiesBufferSize, ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK);
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::TAI_REGISTRY],		Memory::s_TextureAccessIndexBufferSize, ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK);
			
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::ANIMATION_REGISTRY],		Memory::s_AnimationOffsetBufferSize, ORI_MAX_ANIMATION_PER_UNIFORM_BLOCK);
			

			//// Link Buffer array animtion
		/*	auto& animation_array = s_UniformBuffersArray[Memory::UniformBufferIDArray::ANIMATION_REGISTRY_ARRAY];

			for (size_t i = 0; i < animation_array.size(); i++)
				CreateLinkUniformBuffer(animation_array[i], Memory::s_AnimationOffsetBufferSize, (200 * 12));
		*/
		}

		GLuint UniformBlockManager::GetNextBlockBindingPoint() { return s_CurrentBlockBindingPoint++; };
		void UniformBlockManager::LinkShader(Shader* _shader)
		{
			for (auto& _iter : s_UniformBuffers)
			{
				RegisterShaderBlock(_shader, _iter.second);
				if(_shader->HasProxy())
					RegisterProxyShaderBlock(_shader, _iter.second);
			}

			for (auto& _iter : s_UniformBuffersArray)
			{
				for (size_t i = 0; i < _iter.second.size(); i++)
				{
					RegisterShaderBlock(_shader, _iter.second[i]);
					if (_shader->HasProxy())
						RegisterProxyShaderBlock(_shader, _iter.second[i]);
				}
			}
		}
		void UniformBlockManager::CreateLinkUniformBuffer(Memory::UniformBuffer& _buffer, size_t _single_mem_block_size, size_t _total_chunk_memory)
		{
			_buffer.SetMaxCapacity(_single_mem_block_size * _total_chunk_memory);

			glGenBuffers(1, &_buffer.Buffer);

			glBindBuffer(GL_UNIFORM_BUFFER, _buffer.Buffer);
			glBufferData(GL_UNIFORM_BUFFER, _single_mem_block_size * _total_chunk_memory, NULL, GL_DYNAMIC_DRAW);

			RegisterShaderBlock(_buffer);

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		void UniformBlockManager::RegisterShaderBlock(Memory::UniformBuffer& _buffer)
		{
			std::vector<int> block_index;


			auto& SHADER_REG = s_ShaderInterface->GetShaderRegistry();
			// Collect block index
			for (auto& _shader : SHADER_REG)
				block_index.push_back(glGetUniformBlockIndex(_shader.second->GetShader(), _buffer.Name.c_str()));

			// Register Binding point
			_buffer.BindingPoint = GetNextBlockBindingPoint();

			int vector_access_idx = 0; // to access the vector data
			for (auto _shader = SHADER_REG.begin(); _shader != SHADER_REG.end(); _shader++, vector_access_idx++)
				glUniformBlockBinding(_shader->second->GetShader(), block_index.at(vector_access_idx), _buffer.BindingPoint);

			glBindBufferBase(GL_UNIFORM_BUFFER, _buffer.BindingPoint, _buffer.Buffer);
		}

		void UniformBlockManager::RegisterShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, _buffer.Buffer);

			int block_index = glGetUniformBlockIndex(_shader->GetShader(), _buffer.Name.c_str());
			glUniformBlockBinding(_shader->GetShader(), block_index, _buffer.BindingPoint);
			glBindBufferBase(GL_UNIFORM_BUFFER, _buffer.BindingPoint, _buffer.Buffer);
		}
		void UniformBlockManager::RegisterProxyShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, _buffer.Buffer);

			int block_index = glGetUniformBlockIndex(_shader->GetShaderProxy(), _buffer.Name.c_str());
			glUniformBlockBinding(_shader->GetShaderProxy(), block_index, _buffer.BindingPoint);
			glBindBufferBase(GL_UNIFORM_BUFFER, _buffer.BindingPoint, _buffer.Buffer);
		}
	}
}