#include "ShaderManager.h"


namespace OE1Core
{
	ShaderManager::ShaderManager()
	{
		InitShaders();
	}
	ShaderManager::~ShaderManager()
	{
		for (auto _iter : s_Shaders)
			delete _iter.second;
		s_Shaders.clear();
	}

	void ShaderManager::InitShaders()
	{
		LOG_WARRNING("\n");
		AddShaderFromDefaultPath("OES_ModelPreview.shader", ShaderID::MODEL_PREVIEW);
		AddShaderFromDefaultPath("OES_Grid.shader", ShaderID::INIF_GRID);
		AddShaderFromDefaultPath("OES_ObjectOutline.shader", ShaderID::OBJECT_OUTLINE);
	}
	void ShaderManager::AddShader(std::string _path, ShaderID _id, std::string _name)
	{
		if (s_Shaders.find(_id) != s_Shaders.end())
		{
			LOG_ERROR("Shader already exist: {0}", _path);
			return;
		}
		s_Shaders.insert(std::make_pair(_id, new Shader(_path)));
	}
	void ShaderManager::AddShaderFromDefaultPath(std::string _name, ShaderID _id)
	{
		LOG_WARRNING("Processing: {0}", _name);
		AddShader(s_DefaultShaderSourcePath + _name, _id, _name);
	}
	Shader* ShaderManager::GetShader(ShaderID _id)
	{
		if (s_Shaders.find(_id) == s_Shaders.end())
			return nullptr;
		return s_Shaders[_id];
	}
	ShaderManager::ShaderRegistry& ShaderManager::GetShaderRegistry()
	{
		return s_Shaders;
	}
}