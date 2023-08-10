#ifndef OE_SHADER_DATA_H_
#define OE_SHADER_DATA_H_

#include <string>
#include <unordered_map>



// marker
#define VERTEX_SHADER_MARKER						"@ENGINE_MARKER_VS"
#define FRAGMENT_SHADER_MARKER						"@ENGINE_MARKER_FS"
#define GEOMETRY_SHADER_MARKER						"@ENGINE_MARKER_GS"
#define TESSELLATION_CONTROL_SHADER_MARKER			"@ENGINE_MARKER_TCS"
#define TESSELLATION_EVALUATION_SHADER_MARKER		"@ENGINE_MARKER_TES"

// post process directive
#define POST_PROCESS_INCLUDE_MARKER   	"#include "
#define POST_PROCESS_INCLUDE_START		'<'
#define POST_PROCESS_INCLUDE_END		'>'

// util
#define ZERO_SHADER "%%ZERO_SHADER%%"
#define SHADER_ERROR_LOG_BUFFER_SIZE 1024


namespace OE1Core
{
	struct ShaderArg
	{
		// IDs
		unsigned int RenderID;
		unsigned int Program;
		unsigned int VertexShader;
		unsigned int FragmentShader;
		unsigned int TessellationControlShader;
		unsigned int TessellationEvaluationShader;
		unsigned int GeometryShader;

		// bind slote
		std::unordered_map<std::string, int> ShaderTextureUnits;

		// Flags
		int Compiled;
		int Linked;
		char Log[SHADER_ERROR_LOG_BUFFER_SIZE];

		// Source
		std::string VertexShaderSource;
		std::string FragmentShaderSource;
		std::string TessellationControlShaderSource;
		std::string TessellationEvaluationShaderSource;
		std::string GeometryShaderSource;

		// flag
		bool HasTessellationShader	= false;
		bool HasGeometryShader		= false;
		bool IsExternalFile			= false;
		bool SuccessfullLoad		= true;

		// path

		/// Single Shader file Source Path 
		std::string ShaderPath;
		std::string VertexShaderPath;
		std::string FragmentShaderPath;
		std::string TessellationControlShaderPath;
		std::string TessellationEvaluationShaderPath;
		std::string GeometryShaderPath;
	};
}


#endif // !OE_SHADER_DATA_H_
