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
			std::string _vert_shader_proxy = std::string(),
			std::string _geom_path		= std::string(),
			std::string _tess_ctr_path	= std::string(),
			std::string _tess_eva_path	= std::string());
		Shader(const char* _source);
		Shader(const char* _vert_src, const char* _frag_src,
			const char* _vert_src_proxy = nullptr,
			const char* _geom_src = nullptr,
			const char* _tess_ctr_src = nullptr,
			const char* _tess_eva_src = nullptr);
		~Shader();


	public:
		unsigned int GetShader();
		unsigned int GetShaderProxy();
		void Attach();
		void AttachProxy();
		void Detach();
		void Recompile();
		void RegisterTextureUnit(std::string _texture_unit_id, int _slot);
		void PurgTextureUnit(std::string _texture_unit_id);
		void CloneUniformTextureUnit(Shader* _shader);
		/// <summary>
		/// Do not use this for rendering purpose it won't work
		/// </summary>
		void AttachTextureUnit();
		bool HasProxy();

	public:
		std::string& VertSource();
		std::string& FragSource();
		std::string& GeomSource();
		std::string& TessCtrSource();
		std::string& TessEvaSource();

	public:
		void UpdateVertexShader(std::string _vert_shader = std::string());
		void UpdateFragmentShader(std::string _frag_shader = std::string());
		void UpdateGeomShader(std::string _geom_Shader = std::string());
		void UpdateTessShader(std::string _tess_ctr_shader = std::string(), std::string _tess_eva_shader = std::string());




	public:
		void SetProxyMat4(std::string _id, glm::mat4 _mat4);
		void SetProxyMat3(std::string _id, glm::mat3 _mat3);
		void SetProxy1f(std::string _id, float _val);
		void SetProxy2f(std::string _id, glm::vec2 _val);
		void SetProxy3f(std::string _id, glm::vec3 _val);
		void SetProxy4f(std::string _id, glm::vec4 _val);
		void SetProxy1i(std::string _id, int _val);
		void SetProxy2i(std::string _id, glm::ivec2 _val);
		void SetProxy3i(std::string _id, glm::ivec3 _val);
		void SetProxy4i(std::string _id, glm::ivec4 _val);

		void SetMat4(std::string _id, glm::mat4 _mat4);
		void SetMat3(std::string _id, glm::mat3 _mat3);
		void Set1f(std::string _id, float _val);
		void Set2f(std::string _id, glm::vec2 _val);
		void Set3f(std::string _id, glm::vec3 _val);
		void Set4f(std::string _id, glm::vec4 _val);
		void Set1i(std::string _id, int _val);
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
		void CreateCompileShader(unsigned int& _shader_id, std::string& _source, std::string& _normalized_shader, GLenum _shader_type);
		void CreateLinkProgram();


		void UpdateShaderSource(GLuint _shader_id, std::string _shader_name_text, std::string _new_source, std::string& _base_source, std::string& _normalized_source);
		void UpdateShaderLinkage();


		void CompileShader(unsigned int& _shader_id, std::string& _source);
		void LinkProgram();
	protected: // util
		bool IsInValidRange(size_t _index, const std::string& _buffer);
		size_t GetNextValidIndex(size_t _currrent_index, std::vector<size_t>& _list, const std::string& _buffer);
		bool m_HasProxy = false;

	protected:
		ShaderArg m_Arg;
		ShaderArg m_Proxy;
		
	};
}


#endif // !OE_SHADER_H_
