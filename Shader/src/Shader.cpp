#include "Shader.h"


namespace OE1Core
{
	Shader::Shader(std::string _path)
	{
		m_Arg.IsExternalFile = true;
		ProcessPackedShaderSource(ReadDiskFile(_path));
		
		InitShader();
	}
	Shader::Shader(
		std::string _vert_path, 
		std::string _frag_path,
		std::string _vert_proxy_path,
		std::string _geom_path,
		std::string _tess_ctr_path,
		std::string _tess_eva_path)
	{
		m_Arg.IsExternalFile = true;

		// This two are MUST
		m_Arg.VertexShaderSource = ReadDiskFile(_vert_path);
		m_Arg.FragmentShaderSource = ReadDiskFile(_frag_path);

		if (!_vert_proxy_path.empty())
		{
			m_Proxy.VertexShaderSource = ReadDiskFile(_vert_proxy_path);
			m_HasProxy = true;
		}

		// optional
		if (!_geom_path.empty())
		{
			m_Arg.GeometryShaderSource = ReadDiskFile(_geom_path);
			m_Arg.GeometryShaderSource = ZERO_SHADER;
			m_Arg.HasGeometryShader = true;
		}
		else
		{
			m_Arg.HasGeometryShader = false;
			m_Arg.GeometryShaderSource = ZERO_SHADER;
		}

		if (!_tess_ctr_path.empty())
		{
			m_Arg.TessellationControlShaderSource = ReadDiskFile(_tess_ctr_path);
			m_Arg.HasTessellationShader = true;
		}
		else
		{
			m_Arg.HasTessellationShader = false;
			m_Arg.TessellationControlShaderSource = ZERO_SHADER;
		}

		if (!_tess_eva_path.empty())
		{
			m_Arg.TessellationEvaluationShaderSource = ReadDiskFile(_tess_eva_path);
			m_Arg.HasTessellationShader = true;
		}
		else
		{
			m_Arg.TessellationEvaluationShaderSource = ZERO_SHADER;
			m_Arg.HasTessellationShader = false;
		}

		InitShader();
	}
	Shader::Shader(const char* _source)
	{
		m_Arg.IsExternalFile = false;

		ProcessPackedShaderSource(_source);
		
		InitShader();
	}
	Shader::Shader(const char* _vert_src, const char* _frag_src,
		const char* _vert_src_proxy,
		const char* _geom_src,
		const char* _tess_ctr_src,
		const char* _tess_eva_src)
	{
		m_Arg.IsExternalFile = false;

		ProcessShaderDirective(m_Arg.VertexShaderSource = _vert_src);
		ProcessShaderDirective(m_Arg.FragmentShaderSource = _frag_src);

		if (_vert_src_proxy)
		{
			ProcessShaderDirective(m_Proxy.VertexShaderSource = _vert_src_proxy);
			m_HasProxy = true;
		}
		
		// optional
		if (_geom_src)
		{
			ProcessShaderDirective(m_Arg.GeometryShaderSource = _geom_src);
			m_Arg.HasGeometryShader = true;
		}
		else
		{
			m_Arg.GeometryShaderSource = ZERO_SHADER;
			m_Arg.HasGeometryShader = false;
		}

		if (_tess_ctr_src)
		{
			ProcessShaderDirective(m_Arg.TessellationControlShaderSource = _tess_ctr_src);
			m_Arg.HasTessellationShader = true;
		}
		else
		{
			m_Arg.TessellationControlShaderSource = ZERO_SHADER;
			m_Arg.HasTessellationShader = false;
		}

		if (_tess_eva_src)
		{
			ProcessShaderDirective(m_Arg.TessellationEvaluationShaderSource = _tess_eva_src);
			m_Arg.HasTessellationShader = true;
		}
		else
		{
			m_Arg.HasTessellationShader = false;
			m_Arg.TessellationEvaluationShaderSource = ZERO_SHADER;
		}


		InitShader();

	}
	Shader::~Shader()
	{
		glDeleteShader(m_Arg.VertexShader);
		glDeleteShader(m_Arg.FragmentShader);

		glDeleteProgram(m_Arg.RenderID);


		if (m_HasProxy)
		{
			glDeleteShader(m_Proxy.VertexShader);
			glDeleteShader(m_Proxy.FragmentShader);
			glDeleteProgram(m_Proxy.RenderID);
		}
	}
	void Shader::Recompile()
	{
		CompileShader(m_Arg.VertexShader, m_Arg.VertexShaderSource);
		CompileShader(m_Arg.FragmentShader, m_Arg.FragmentShaderSource);

		if (m_Arg.HasGeometryShader)
			CompileShader(m_Arg.GeometryShader, m_Arg.GeometryShaderSource);

		if (m_Arg.HasTessellationShader)
		{
			CompileShader(m_Arg.TessellationControlShader, m_Arg.TessellationControlShaderSource);
			CompileShader(m_Arg.TessellationEvaluationShader, m_Arg.TessellationEvaluationShaderSource);
		}

		LinkProgram();
	}
	void Shader::InitShader()
	{
		if (!m_Arg.SuccessfullLoad)
		{
			LOG_ERROR("An Error Occurred During the Loading Process. The Operation Has Been Aborted.");
			return;
		}
		if (m_HasProxy)
		{
			CreateCompileShader(m_Proxy.VertexShader, m_Proxy.VertexShaderSource, GL_VERTEX_SHADER);
			CreateCompileShader(m_Proxy.FragmentShader, m_Arg.FragmentShaderSource, GL_FRAGMENT_SHADER);

		}
		CreateCompileShader(m_Arg.VertexShader, m_Arg.VertexShaderSource,			GL_VERTEX_SHADER);
		CreateCompileShader(m_Arg.FragmentShader, m_Arg.FragmentShaderSource,		GL_FRAGMENT_SHADER);
		
		if(m_Arg.HasGeometryShader)
			CreateCompileShader(m_Arg.GeometryShader, m_Arg.GeometryShaderSource,	GL_GEOMETRY_SHADER);
		
		if (m_Arg.HasTessellationShader)
		{
			CreateCompileShader(m_Arg.TessellationControlShader, m_Arg.TessellationControlShaderSource, GL_TESS_CONTROL_SHADER);
			CreateCompileShader(m_Arg.TessellationEvaluationShader, m_Arg.TessellationEvaluationShaderSource, GL_TESS_EVALUATION_SHADER);
		}

		CreateLinkProgram();
	}
	bool Shader::IsInValidRange(size_t _index, const std::string& _buffer)
	{
		if (_index >= 0 && _index <= _buffer.size())
			return true;
		return false;
	}
	size_t Shader::GetNextValidIndex(size_t _currrent_index, std::vector<size_t>& _list, const std::string& _buffer)
	{
		for (size_t i = _currrent_index; i < _list.size(); i++)
			if (IsInValidRange(_list[i], _buffer))
				return _list[i];
		return size_t(0);
	}
	void Shader::AcquireShaderCode(std::string& _shader_source_dest, std::vector<std::string>& _shader_source_list, std::string _marker)
	{
		// help to ignore the marker text it self
		size_t marker_char_count = _marker.size();

		for (size_t i = 0; i < _shader_source_list.size(); i++)
		{
			if (_shader_source_list[i].find(_marker) != std::string::npos)
			{
				_shader_source_dest = _shader_source_list[i].substr(marker_char_count, _shader_source_list[i].size());
				return;
			}
		}
		 
		_shader_source_dest = ZERO_SHADER;
	}
	void Shader::ProcessPackedShaderSource(std::string _source_code)
	{
		size_t vertex_shader_begin_marker_index						=	_source_code.find(VERTEX_SHADER_MARKER);
		size_t fragment_shader_begin_marker_index					=	_source_code.find(FRAGMENT_SHADER_MARKER);
		size_t geometry_shader_begin_marker_index					=	_source_code.find(GEOMETRY_SHADER_MARKER);
		size_t tessellation_control_shader_begin_marker_index		=	_source_code.find(TESSELLATION_CONTROL_SHADER_MARKER);
		size_t tessellation_evaluation_shader_begin_marker_index	=	_source_code.find(TESSELLATION_EVALUATION_SHADER_MARKER);

		std::vector<size_t> shader_source_begin_marker_index
		{ 
				vertex_shader_begin_marker_index,
				geometry_shader_begin_marker_index,
				tessellation_control_shader_begin_marker_index,
				tessellation_evaluation_shader_begin_marker_index,
				fragment_shader_begin_marker_index
		};


		std::vector<std::string> source_code_list;
		for (int i = 0; i < 5; i++)
		{
			if (IsInValidRange(shader_source_begin_marker_index[i], _source_code))
			{
				size_t nextValidIndex = GetNextValidIndex(i + 1, shader_source_begin_marker_index, _source_code);
				if (i == 4)
					source_code_list.push_back(_source_code.substr(shader_source_begin_marker_index[i], _source_code.size() - shader_source_begin_marker_index[i]));
				else
					source_code_list.push_back(_source_code.substr(shader_source_begin_marker_index[i], nextValidIndex - shader_source_begin_marker_index[i]));
			}
		}

		AcquireShaderCode(m_Arg.VertexShaderSource,						source_code_list,	VERTEX_SHADER_MARKER);
		AcquireShaderCode(m_Arg.FragmentShaderSource,					source_code_list,	FRAGMENT_SHADER_MARKER);
		AcquireShaderCode(m_Arg.GeometryShaderSource,					source_code_list,	GEOMETRY_SHADER_MARKER);
		AcquireShaderCode(m_Arg.TessellationControlShaderSource,		source_code_list,	TESSELLATION_CONTROL_SHADER_MARKER);
		AcquireShaderCode(m_Arg.TessellationEvaluationShaderSource,		source_code_list,	TESSELLATION_EVALUATION_SHADER_MARKER);


		if (m_Arg.VertexShaderSource == ZERO_SHADER || m_Arg.FragmentShaderSource == ZERO_SHADER)
		{
			LOG_ERROR("Invalid Shader Source!");
			m_Arg.SuccessfullLoad = false;
			return;
		}

		if (m_Arg.GeometryShaderSource == ZERO_SHADER)
			m_Arg.HasGeometryShader = false;
		if ((m_Arg.TessellationControlShaderSource == ZERO_SHADER) || (m_Arg.TessellationEvaluationShaderSource == ZERO_SHADER))
			m_Arg.HasTessellationShader = false;
		m_Arg.SuccessfullLoad = true;
	}
	void Shader::ProcessShaderDirective(std::string& _shader_source)
	{
		while (_shader_source.find(POST_PROCESS_INCLUDE_MARKER) != _shader_source.npos)
		{
			const auto marker_pos					= _shader_source.find(POST_PROCESS_INCLUDE_MARKER);
			const auto marker_content_start_pos		= _shader_source.find(POST_PROCESS_INCLUDE_START);
			const auto marker_content_end_pos		= _shader_source.find(POST_PROCESS_INCLUDE_END);

			if (
				marker_pos == _shader_source.npos ||
				marker_content_start_pos == _shader_source.npos ||
				marker_content_end_pos == _shader_source.npos
				)
			{
				LOG_ERROR("Invalid Postprocess Directive!");
				m_Arg.SuccessfullLoad = false;
				break;
			}

			const std::string shader_path_in_directive = _shader_source.substr(marker_content_start_pos + 1, marker_content_end_pos - marker_content_start_pos - 1);
			std::string included_shader_source = ReadDiskFile(shader_path_in_directive);
			_shader_source.replace(marker_pos, marker_content_end_pos - marker_pos + 1, included_shader_source.c_str());
		}
	}
	std::string Shader::ReadDiskFile(std::string _path)
	{
		std::ifstream disk_file(_path, std::ios::in);
		if (!disk_file.is_open())
		{
			LOG_ERROR("Failed to open file {0} ", _path);
			m_Arg.SuccessfullLoad = false;
			return "%%ORION_CRITICAL_ERROR%%";
		}

		std::string temp_buffer;
		std::string shader_source;

		while (getline(disk_file, temp_buffer))
			shader_source += temp_buffer + "\n";

		// if the loaded source code contain any include directive recursivly load it
		ProcessShaderDirective(shader_source);

		return shader_source;
	}

	void Shader::CreateCompileShader(unsigned int& _shader_id, std::string& _source, GLenum _shader_type)
	{
		_shader_id = glCreateShader(_shader_type);
		const char* source_code = _source.c_str();
		glShaderSource(_shader_id, 1, &source_code, NULL);
		glCompileShader(_shader_id);

		glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &m_Arg.Compiled);
		if (!m_Arg.Compiled)
		{
			glGetShaderInfoLog(_shader_id, SHADER_ERROR_LOG_BUFFER_SIZE, NULL, m_Arg.Log);
			LOG_ERROR(m_Arg.Log);
		}
	}
	void Shader::CreateLinkProgram()
	{
		m_Arg.RenderID = glCreateProgram();
		glAttachShader(m_Arg.RenderID, m_Arg.VertexShader);

		if(m_Arg.HasGeometryShader)
			glAttachShader(m_Arg.RenderID, m_Arg.GeometryShader);

		if (m_Arg.HasTessellationShader)
		{
			glAttachShader(m_Arg.RenderID, m_Arg.TessellationControlShader);
			glAttachShader(m_Arg.RenderID, m_Arg.TessellationEvaluationShader);
		}

		glAttachShader(m_Arg.RenderID, m_Arg.FragmentShader);

		glLinkProgram(m_Arg.RenderID);

		glGetProgramiv(m_Arg.RenderID, GL_LINK_STATUS, &m_Arg.Linked);

		if (!m_Arg.Linked)
		{
			glGetProgramInfoLog(m_Arg.RenderID, SHADER_ERROR_LOG_BUFFER_SIZE, NULL, m_Arg.Log);
			LOG_ERROR(m_Arg.Log);
		}


		if (m_HasProxy)
		{
			m_Proxy.RenderID = glCreateProgram();
			glAttachShader(m_Proxy.RenderID, m_Proxy.VertexShader);
			if (m_Arg.HasGeometryShader)
				glAttachShader(m_Proxy.RenderID, m_Arg.GeometryShader);

			if (m_Arg.HasTessellationShader)
			{
				glAttachShader(m_Proxy.RenderID, m_Arg.TessellationControlShader);
				glAttachShader(m_Proxy.RenderID, m_Arg.TessellationEvaluationShader);
			}

			glAttachShader(m_Proxy.RenderID, m_Arg.FragmentShader);


			glLinkProgram(m_Proxy.RenderID);

			glGetProgramiv(m_Proxy.RenderID, GL_LINK_STATUS, &m_Proxy.Linked);

			if (!m_Arg.Linked)
			{

				glGetProgramInfoLog(m_Proxy.RenderID, SHADER_ERROR_LOG_BUFFER_SIZE, NULL, m_Proxy.Log);
				LOG_ERROR("PROXY_SHADER");
				LOG_ERROR(m_Proxy.Log);
			}

		}
	}

	void Shader::LinkProgram()
	{
		glAttachShader(m_Arg.RenderID, m_Arg.VertexShader);

		if (m_Arg.HasGeometryShader)
			glAttachShader(m_Arg.RenderID, m_Arg.GeometryShader);

		if (m_Arg.HasTessellationShader)
		{
			glAttachShader(m_Arg.RenderID, m_Arg.TessellationControlShader);
			glAttachShader(m_Arg.RenderID, m_Arg.TessellationEvaluationShader);
		}

		glAttachShader(m_Arg.RenderID, m_Arg.FragmentShader);

		glLinkProgram(m_Arg.RenderID);

		glGetProgramiv(m_Arg.RenderID, GL_LINK_STATUS, &m_Arg.Linked);

		if (!m_Arg.Linked)
		{
			glGetProgramInfoLog(m_Arg.RenderID, SHADER_ERROR_LOG_BUFFER_SIZE, NULL, m_Arg.Log);
			LOG_ERROR(m_Arg.Log);
		}
	}

	void Shader::CompileShader(unsigned int& _shader_id, std::string& _source)
	{
		const char* source_code = _source.c_str();
		glShaderSource(_shader_id, 1, &source_code, NULL);
		glCompileShader(_shader_id);

		glGetShaderiv(_shader_id, GL_COMPILE_STATUS, &m_Arg.Compiled);
		if (!m_Arg.Compiled)
		{
			glGetShaderInfoLog(_shader_id, SHADER_ERROR_LOG_BUFFER_SIZE, NULL, m_Arg.Log);
			LOG_ERROR(m_Arg.Log);
		}
	}
	void Shader::RegisterTextureUnit(std::string _texture_unit_id, int _slot)
	{
		if (m_Arg.ShaderTextureUnits.find(_texture_unit_id) != m_Arg.ShaderTextureUnits.end())
		{
			LOG_WARRNING("Texture Unit updated FROM [{0} = {1}]  TO  [{2} = {3}]", _texture_unit_id, m_Arg.ShaderTextureUnits[_texture_unit_id], _texture_unit_id, _slot);
		}
		m_Arg.ShaderTextureUnits[_texture_unit_id] = _slot;
	}
	void Shader::PurgTextureUnit(std::string _texture_unit_id)
	{
		if (m_Arg.ShaderTextureUnits.find(_texture_unit_id) != m_Arg.ShaderTextureUnits.end())
			m_Arg.ShaderTextureUnits.erase(_texture_unit_id);
	}
	void Shader::CloneUniformTextureUnit(Shader* _shader)
	{
		m_Arg.ShaderTextureUnits.clear();
		m_Arg.ShaderTextureUnits = _shader->m_Arg.ShaderTextureUnits;
		AttachTextureUnit();
	}
	bool Shader::HasProxy() { return m_HasProxy; }
	void Shader::AttachTextureUnit()
	{
		Attach();

		for (auto& iter : m_Arg.ShaderTextureUnits)
			set1i(iter.first, iter.second);

		Detach();

		if (m_HasProxy)
		{
			AttachProxy();

			for (auto& iter : m_Arg.ShaderTextureUnits)
				setProxy1i(iter.first, iter.second);

			Detach();
		}
	}
	unsigned int Shader::GetShader()
	{
		return m_Arg.RenderID;
	}
	unsigned int Shader::GetShaderProxy()
	{
		return m_Proxy.RenderID;
	}
	void Shader::Attach()
	{
		glUseProgram(m_Arg.RenderID);
	}
	void Shader::AttachProxy()
	{
		glUseProgram(m_Proxy.RenderID);
	}
	void Shader::Detach()
	{
		/*   https://registry.khronos.org/OpenGL-Refpages/gl4/html/glUseProgram.xhtml
		If program is zero, then the current rendering state refers to an invalid program object
		and the results of shader execution are undefined.
		However, this is not an error.

		If program does not contain shader objects of type GL_FRAGMENT_SHADER,
		an executable will be installed on the vertex, and possibly geometry processors,
		but the results of fragment shader execution will be undefined.
		*/
		glUseProgram(0);
	}
	std::string& Shader::VertSource()		{ return m_Arg.VertexShaderSource; }
	std::string& Shader::FragSource()		{ return m_Arg.FragmentShaderSource; }
	std::string& Shader::GeomSource()		{ return m_Arg.GeometryShaderSource; }
	std::string& Shader::TessCtrSource()	{ return m_Arg.TessellationControlShaderSource; }
	std::string& Shader::TessEvaSource()	{ return m_Arg.TessellationEvaluationShaderSource; }



	void Shader::SetMat4(std::string _id, glm::mat4 _mat4)
	{
		glUniformMatrix4fv(
			glGetUniformLocation(m_Arg.RenderID, _id.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(_mat4));
	}
	void Shader::SetMat3(std::string _id, glm::mat3 _mat3)
	{
		glUniformMatrix3fv(
			glGetUniformLocation(m_Arg.RenderID, _id.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(_mat3));
	}
	void Shader::Set1f(std::string _id, float _val)
	{
		glUniform1f(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), _val);
	}
	void Shader::set2f(std::string _id, glm::vec2 _val)
	{
		glUniform2fv(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::set3f(std::string _id, glm::vec3 _val)
	{
		glUniform3fv(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::set4f(std::string _id, glm::vec4 _val)
	{
		glUniform4fv(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::set1i(std::string _id, int _val)
	{
		glUniform1i(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), _val);
	}
	void Shader::Set2i(std::string _id, glm::ivec2 _val)
	{
		glUniform2i(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), _val.x, _val.y);
	}
	void Shader::Set3i(std::string _id, glm::ivec3 _val)
	{
		glUniform3i(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), _val.x, _val.y, _val.z);
	}
	void Shader::Set4i(std::string _id, glm::ivec4 _val)
	{
		glUniform4i(glGetUniformLocation(m_Arg.RenderID, _id.c_str()), _val.x, _val.y, _val.z, _val.w);
	}


	// PROXY
	void Shader::SetProxyMat4(std::string _id, glm::mat4 _mat4)
	{
		glUniformMatrix4fv(
			glGetUniformLocation(m_Proxy.RenderID, _id.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(_mat4));
	}
	void Shader::SetProxyMat3(std::string _id, glm::mat3 _mat3)
	{
		glUniformMatrix3fv(
			glGetUniformLocation(m_Proxy.RenderID, _id.c_str()),
			1,
			GL_FALSE,
			glm::value_ptr(_mat3));
	}
	void Shader::SetProxy1f(std::string _id, float _val)
	{
		glUniform1f(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), _val);
	}
	void Shader::setProxy2f(std::string _id, glm::vec2 _val)
	{
		glUniform2fv(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::setProxy3f(std::string _id, glm::vec3 _val)
	{
		glUniform3fv(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::setProxy4f(std::string _id, glm::vec4 _val)
	{
		glUniform4fv(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), 1, glm::value_ptr(_val));
	}
	void Shader::setProxy1i(std::string _id, int _val)
	{
		glUniform1i(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), _val);
	}
	void Shader::SetProxy2i(std::string _id, glm::ivec2 _val)
	{
		glUniform2i(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), _val.x, _val.y);
	}
	void Shader::SetProxy3i(std::string _id, glm::ivec3 _val)
	{
		glUniform3i(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), _val.x, _val.y, _val.z);
	}
	void Shader::SetProxy4i(std::string _id, glm::ivec4 _val)
	{
		glUniform4i(glGetUniformLocation(m_Proxy.RenderID, _id.c_str()), _val.x, _val.y, _val.z, _val.w);
	}

}