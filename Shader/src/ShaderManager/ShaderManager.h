#ifndef OE1_SHADER_MANAGER_H_
#define OE1_SHADER_MANAGER_H_


// ORion
#include "../Shader.h"
#include "ShaderID.h"


// SL
#include <unordered_map>


// Suppress warning C4251: 'std::unordered_map' needs to have dll-interface to be used by clients.
// Explanation: We suppress this warning because we are exporting 'std::unordered_map' as part of our DLL
// interface, which is required for this specific project's functionality. The warning doesn't indicate
// an issue with our code but rather a necessary configuration for our DLL.
#pragma warning(disable: 4251)

namespace OE1Core
{
	namespace Memory { class UniformBlockManager;  }
	class __declspec(dllexport) ShaderManager
	{
		friend class Memory::UniformBlockManager;
		friend class CoreSystem;
		friend class ShaderSystem;
	public:
		ShaderManager();
		~ShaderManager();

		using ShaderRegistry = std::unordered_map<ShaderID, Shader*>;
		// This might return nullptr
		static Shader* GetShader(ShaderID _id);
		static ShaderRegistry& GetShaderRegistry();

	private:
		inline static std::unordered_map<ShaderID, Shader*> s_Shaders;
	private: // Util
		static void AddShader(std::string _path, ShaderID _id, std::string _shader_name);
		static void AddShaderFromDefaultPath(std::string _name, ShaderID _id);
		static void InitShaders();

	private:
		inline static const std::string s_DefaultShaderSourcePath = "../ExternalAsset/Shaders/";


	};
}

#endif // !OE1_SHADER_MANAGER_H_
