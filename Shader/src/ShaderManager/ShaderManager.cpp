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
		AddShaderFromDefaultPath("OES_2DTextureArrayExtract.shader", ShaderID::TEXTURE_2D_ARRAY_EXTRACTOR);
		AddShaderFromDefaultPath("OES_ViewportBillboardIconTexturePass.shader", ShaderID::VIEWPORT_BILLBOARD_ICON_TEXTURE_PASS);
		AddShaderFromDefaultPath("OES_MaterialPreview.shader", ShaderID::MATERIAL_PREVIEW);
		AddShaderFromDefaultPath("OES_LocalDebugShape.shader", ShaderID::LOCAL_DEBUG_SHAPE);
		AddShaderFromDefaultPath("OES_SceneDebugShape.shader", ShaderID::SCENE_DEBUG_SHAPE);
		AddShaderFromDefaultPath("OES_FullScreenQuad.shader",	ShaderID::FULL_SCREEN_QUAD);
		AddShaderFromDefaultPath("OES_DefferedLightPass.shader", ShaderID::DEFFERED_LIGHT_PASS);
		AddShaderFromDefaultPath("OES_Skybox.shader", ShaderID::SKYBOX);

		AddShaderFromDefaultPath("IBL/OES_ConvertHDRI.shader", ShaderID::TO_CUBEMAP);
		AddShaderFromDefaultPath("IBL/OES_GenerateIrradiance.shader", ShaderID::TO_IRRADIANCEMAP);

		AddShaderFromDefaultPath("IBL/OES_PrefilterEnvironment.shader", ShaderID::PREFILTERD_ENV_MAP);
		AddShaderFromDefaultPath("IBL/OES_PreBRDF.shader", ShaderID::PRE_BRDF_MAP);
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
	Shader* ShaderManager::ReLoadShader(ShaderID _id)
	{
		if (s_Shaders.find(_id) == s_Shaders.end())
			return nullptr;

		Shader* _shader = s_Shaders[_id];

		//_shader->Recompile();

		return _shader;
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