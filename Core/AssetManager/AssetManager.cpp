#include "AssetManager.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	AssetManager::AssetManager()
	{

	}
	AssetManager::~AssetManager()
	{
		for (auto iter : s_TextureRegistry)
			delete iter.second;
	}
	void AssetManager::RegisterImage(std::string _path, std::string _name)
	{
		DataBlock::Image2D image_raw = Loader::TextureLoader::OELoadImage(_path);
		if (!image_raw.Valid)
			return;
		// make sure this image or at least another image with the same name
		bool name_exist = (s_TextureRegistry.find(_name) != s_TextureRegistry.end());
		if (name_exist)
		{
			stbi_image_free(image_raw.Data);
			return; // Just ignore it for now
		}

		s_TextureRegistry.insert(std::make_pair(_name, new Texture(image_raw)));
	}
	void AssetManager::RegisterHDRIImage(std::string _path, std::string _name)
	{
		DataBlock::ImageHDRI image_raw_hdri = Loader::TextureLoader::OELoadHDRI(_path);
		if (!image_raw_hdri.Valid)
			return;
		// make sure this image or at least another image with the same name
		bool name_exist = (s_TextureHDRIRegistry.find(_name) != s_TextureHDRIRegistry.end());
		if (name_exist)
		{
			stbi_image_free(image_raw_hdri.Data);
			return; // Just ignore it for now
		}

		s_TextureRegistry.insert(std::make_pair(_name, new Texture(image_raw_hdri)));
	}
	Texture* AssetManager::GetTexture(std::string _name)
	{
		if (auto iter = s_TextureRegistry.find(_name) == s_TextureRegistry.end())
			return nullptr;

		return s_TextureRegistry[_name];
	}
	Texture* AssetManager::GetTextureHDRI(std::string _name)
	{
		if (auto iter = s_TextureHDRIRegistry.find(_name) == s_TextureHDRIRegistry.end())
			return nullptr;

		return s_TextureHDRIRegistry[_name];
	}


	ModelPkg* AssetManager::GetGeometry(uint32_t _model_id)
	{
		if(s_RenderableGeometryIDTranslator.find(_model_id) == s_RenderableGeometryIDTranslator.end())
			return nullptr;
		return &s_RenderableGeometry[s_RenderableGeometryIDTranslator[_model_id]];
	}
	ModelPkg* AssetManager::GetGeometry(std::string _name)
	{
		if (s_RenderableGeometry.find(_name) == s_RenderableGeometry.end())
			return nullptr;
		return &s_RenderableGeometry[_name];
	}
	void AssetManager::RegisterGeometry(ModelPkg _model)
	{
		uint32_t model_id = _model.PackageID;
		std::string model_name = _model.Name;

		if (s_RenderableGeometry.find(model_name) != s_RenderableGeometry.end())
			return;
		s_RenderableGeometryIDTranslator.insert(std::make_pair(model_id, model_name));
		s_RenderableGeometry.insert(std::make_pair(model_name, _model));
	}
}