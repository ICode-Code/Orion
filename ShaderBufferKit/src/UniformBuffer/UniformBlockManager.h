#ifndef OE1_UNIFORM_BLOCK_MANAGER_H_
#define OE1_UNIFORM_BLOCK_MANAGER_H_


#include "Interface/ShaderInterface.h"
#include "Shared/UniformBlocks.h"
#include "Shared/PreDef.h"

#include <unordered_map>



// Suppress warning C4251: 'std::unordered_map' needs to have dll-interface to be used by clients.
// Explanation: We suppress this warning because we are exporting 'std::unordered_map' as part of our DLL
// interface, which is required for this specific project's functionality. The warning doesn't indicate
// an issue with our code but rather a necessary configuration for our DLL.
#pragma warning(disable: 4251)

namespace OE1Core
{
	namespace Memory
	{
		/// <summary>
		/// Init this after shader - must
		/// </summary>
		class __declspec(dllexport) UniformBlockManager
		{
		public:
			UniformBlockManager(ShaderInterface* _shader_interface);
			~UniformBlockManager();

			static void LinkShader(Shader* _shader);
			// This function will return nullptr if the id isn't match up
			static Memory::UniformBuffer* GetBuffer(Memory::UniformBufferID _id);
			static Memory::UniformBuffer* GetBuffer(Memory::UniformBufferIDArray _id, int _idx);
			static std::vector<Memory::UniformBuffer>& GetBuffers(Memory::UniformBufferIDArray _id);
			// This function assumes that the ID exists; 
			// Not checking it may lead to crashes.
			// Use this function with caution.
			static Memory::UniformBuffer* UseBuffer(Memory::UniformBufferID _id);

		public: 
			inline static std::unordered_map<Memory::UniformBufferID, Memory::UniformBuffer> s_UniformBuffers;
			inline static std::unordered_map<Memory::UniformBufferIDArray, std::vector<Memory::UniformBuffer>> s_UniformBuffersArray;
			inline static Memory::UniformBuffer* s_SceneTransformBuffer = nullptr;


		private: // util
			static GLuint GetNextBlockBindingPoint();
			static void RegisterShaderBlock(Memory::UniformBuffer& _buffer);
			static void RegisterShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer);
			static void RegisterProxyShaderBlock(Shader* _shader, Memory::UniformBuffer& _buffer);
			static void CreateLinkUniformBuffer(Memory::UniformBuffer& _buffer, size_t _single_mem_block_size, size_t _total_chunk_memory);
			static void RegisterUniformBuffers();
			static void LinkUniformBuffers();

		private: // data
			inline static GLuint s_CurrentBlockBindingPoint = 0;
			inline static ShaderInterface* s_ShaderInterface = nullptr;

		};
	}
}

#endif // !OE1_UNIFORM_BLOCK_MANAGER_H_
