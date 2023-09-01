#ifndef OE1_UNIFORM_BLOCK_MANAGER_H_
#define OE1_UNIFORM_BLOCK_MANAGER_H_

#include "../../ShaderManager/ShaderManager.h"
#include "UniformBlocks.h"

#include <unordered_map>

#define UNIFORM_BLOCK_MEMORY_STRESS 256
#define MAX_MATERIAL Memory::UniformBlockManager::MaxUniformBlockSize()

namespace OE1Core
{
	namespace Memory
	{
		/// <summary>
		/// Init this after shader - must
		/// </summary>
		class UniformBlockManager
		{
		public:
			UniformBlockManager();
			~UniformBlockManager();

			static void LinkShader(Shader* _shader);
			static GLuint MaxUniformBlockSize();

		public:
			inline static std::unordered_map<Memory::UniformBufferID, Memory::UniformBuffer> s_UniformBuffers;
			inline static Memory::UniformBuffer* s_SceneTransformBuffer = nullptr;


		private: // util
			static GLuint GetNextBlockBindingPoint();
			static void RegisterShaderBlock(Memory::UniformBuffer& _buffer);
			static void RegisterShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer);
			static void CreateLinkUniformBuffer(Memory::UniformBuffer& _buffer, size_t _single_mem_block_size, size_t _total_chunk_memory);
			static void RegisterUniformBuffers();
			static void LinkUniformBuffers();

		private: // data
			static inline GLuint s_CurrentBlockBindingPoint = 0;

		};
	}
}

#endif // !OE1_UNIFORM_BLOCK_MANAGER_H_
