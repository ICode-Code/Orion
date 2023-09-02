#include "UniformBlockManager.h"


namespace OE1Core
{
	namespace Memory
	{
		UniformBlockManager::UniformBlockManager()
		{
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
		Memory::UniformBuffer* UniformBlockManager::UseBuffer(Memory::UniformBufferID _id)
		{
			return &s_UniformBuffers[_id];
		}
		void UniformBlockManager::RegisterUniformBuffers()
		{
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::SCENE_TRANSFORM,		Memory::UniformBuffer("SceneTransform")));
			s_UniformBuffers.insert(std::make_pair(Memory::UniformBufferID::INFIN_GRID,				Memory::UniformBuffer("InfiniteGrid")));
		}
		void UniformBlockManager::LinkUniformBuffers()
		{
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::SCENE_TRANSFORM], Memory::s_SceneTransformBufferSize, 1);
			CreateLinkUniformBuffer(s_UniformBuffers[Memory::UniformBufferID::INFIN_GRID],		Memory::s_InfiniteGridBufferSize,	1);
		}

		GLuint UniformBlockManager::GetNextBlockBindingPoint() { return s_CurrentBlockBindingPoint++; };

		GLuint UniformBlockManager::MaxUniformBlockSize()
		{
			GLint max_uniform_buff;
			glGetIntegerv(GL_MAX_UNIFORM_BLOCK_SIZE, &max_uniform_buff);
			return max_uniform_buff;
		}
		void UniformBlockManager::LinkShader(Shader* _shader)
		{
			for (auto& _iter : s_UniformBuffers)
				RegisterShaderBlock(_shader, _iter.second);
		}
		void UniformBlockManager::CreateLinkUniformBuffer(Memory::UniformBuffer& _buffer, size_t _single_mem_block_size, size_t _total_chunk_memory)
		{
			glGenBuffers(1, &_buffer.Buffer);

			glBindBuffer(GL_UNIFORM_BUFFER, _buffer.Buffer);
			glBufferData(GL_UNIFORM_BUFFER, _single_mem_block_size * _total_chunk_memory, NULL, GL_DYNAMIC_DRAW);

			RegisterShaderBlock(_buffer);

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
		void UniformBlockManager::RegisterShaderBlock(Memory::UniformBuffer& _buffer)
		{
			std::vector<int> block_index;

			// Collect block index
			for (auto& _shader : ShaderManager::s_Shaders)
				block_index.push_back(glGetUniformBlockIndex(_shader.second->GetShader(), _buffer.Name.c_str()));

			// Register Binding point
			_buffer.BindingPoint = GetNextBlockBindingPoint();

			int vector_access_idx = 0; // to access the vector data
			for (auto _shader = ShaderManager::s_Shaders.begin(); _shader != ShaderManager::s_Shaders.end(); _shader++, vector_access_idx++)
				glUniformBlockBinding(_shader->second->GetShader(), block_index.at(vector_access_idx), _buffer.BindingPoint);

			glBindBufferBase(GL_UNIFORM_BUFFER, _buffer.BindingPoint, _buffer.Buffer);
		}

		void UniformBlockManager::RegisterShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, _buffer.Buffer);

			int block_index = glGetUniformBlockIndex(_shader->GetShader(), _buffer.Name.c_str());
			glUniformBlockBinding(_shader->GetShader(), block_index, _buffer.BindingPoint);
			glBindBufferBase(GL_UNIFORM_BUFFER, _buffer.BindingPoint, _buffer.Buffer);

			glBindBuffer(GL_UNIFORM_BUFFER, 0);
		}
	}
}