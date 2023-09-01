#ifndef OE1_SHADER_MANAGER_H_
#define OE1_SHADER_MANAGER_H_


// ORion
#include <Log.h>
#include <Shader.h>
#include "ShaderID.h"


// SL
#include <unordered_map>

namespace OE1Core
{
	namespace Memory { class UniformBlockManager;  }
	class ShaderManager
	{
		friend class Memory::UniformBlockManager;
	public:
		ShaderManager();
		~ShaderManager();

		// This might return nullptr
		static Shader* GetShader(ShaderID _id);

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
