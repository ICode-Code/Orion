#ifndef OE_SHADER_H_
#define OE_SHADER_H_

#include <GL/glew.h>

#include <Log.h>

#include <fstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


#include "ShaderData.h"

namespace  OE1Core
{
	class Shader
	{
	public:
		Shader(std::string _path);
		Shader(std::string _vert_path, std::string _frag_path,
			std::string _geom_path		= "#",
			std::string _tess_ctr_path	= "#",
			std::string _tess_eva_path	= "#");
		Shader(const char* _source);
		Shader(const char* _vert_src, const char* _frag_src,
			const char* _geom_src = "#",
			const char* _tess_ctr_src = "#",
			const char* _tess_eva_src = "#");
		~Shader();


	public:
		unsigned int GetShader();
		void Attach();
		void Detach();
		void Recompile();
		void RegisterTextureUnit(std::string _texture_unit_id, int _slot);
		void PurgTextureUnit(std::string _texture_unit_id);
		void CloneUniformTextureUnit(Shader* _shader);
		/// <summary>
		/// Do not use this for rendering purpose it won't work
		/// </summary>
		void AttachTextureUnit();

	public:
		std::string& VertSource();
		std::string& FragSource();
		std::string& GeomSource();
		std::string& TessCtrSource();
		std::string& TessEvaSource();


	public:
		void SetMat4(std::string _id, glm::mat4 _mat4);
		void SetMat3(std::string _id, glm::mat3 _mat3);
		void Set1f(std::string _id, float _val);
		void set2f(std::string _id, glm::vec2 _val);
		void set3f(std::string _id, glm::vec3 _val);
		void set4f(std::string _id, glm::vec4 _val);
		void set1i(std::string _id, int _val);
		void Set2i(std::string _id, glm::ivec2 _val);
		void Set3i(std::string _id, glm::ivec3 _val);
		void Set4i(std::string _id, glm::ivec4 _val);


	protected:
		/// <summary>
		/// This function process shader source which is all shader are packed in one file or in one source
		/// </summary>
		/// <param name="_source">Source Code</param>
		void ProcessPackedShaderSource(std::string _source_code);
		void AcquireShaderCode(std::string& _shader_source_dest, std::vector<std::string>& _shader_source_list, std::string _marker);
		void ProcessShaderDirective(std::string& _shader_source);
		std::string ReadDiskFile(std::string _path);
		void InitShader();
		void CreateCompileShader(unsigned int& _shader_id, std::string& _source, GLenum _shader_type);
		void CreateLinkProgram();

		void CompileShader(unsigned int& _shader_id, std::string& _source);
		void LinkProgram();
	protected: // util
		bool IsInValidRange(size_t _index, const std::string& _buffer);
		size_t GetNextValidIndex(size_t _currrent_index, std::vector<size_t>& _list, const std::string& _buffer);
		

	protected:
		ShaderArg m_Arg;
		
	};
}


#endif // !OE_SHADER_H_
