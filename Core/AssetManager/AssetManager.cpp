#include "AssetManager.h"
#include <STBI/stb_image.h>
#include "LogUI.h"

namespace OE1Core
{
	AssetManager::AssetManager()
	{

	}
	AssetManager::~AssetManager()
	{
		for (auto iter : s_TextureRegistry)
			delete iter.second;
		s_TextureRegistry.clear();

		for (auto iter : s_TextureHDRIRegistry)
			delete iter.second;
		s_TextureHDRIRegistry.clear();

		for (auto iter : s_TextureInternalRegistry)
			delete iter.second;
		s_TextureInternalRegistry.clear();
	}
	Texture* AssetManager::RegisterTexture(std::string _path, std::string _name)
	{
		DataBlock::Image2D image_raw = Loader::TextureLoader::OELoadImage(_path);

		return RegisterTexture(image_raw);
	}
	Texture* AssetManager::RegisterTexture(DataBlock::Image2D& _image)
	{
		// make sure this image or at least another image with the same name
		std::string _name = _image.Name; 

		std::string _texture_seed = AssetManager::CreateTextureSeed(_image).c_str();

		if (!_image.Valid)
			return nullptr;
		// make sure this image or at least another image with the same name
		bool name_exist = (s_TextureRegistry.find(_name) != s_TextureRegistry.end());
		if (name_exist)
		{
			// Check seed
			if (s_TextureRegistry[_name]->GetSeed() == _texture_seed)
			{
				LOG_WARRNING(LogLayer::Pipe("Image with the same detected! [" + _name + "]. Returing the original...", OELog::WARNING));
				return s_TextureRegistry[_name];
			}
		}
		// if it reach here the new image is truly new
		// Handle name 
		std::string new_name = Util::UtilFunc::CheckNameCollision(_name, AssetManager::CheckTextureNameExist);

		_image.Name = new_name;
		s_TextureRegistry.insert(std::make_pair(new_name, new Texture(_image)));

		// Set Seed
		s_TextureRegistry[new_name]->SetSeed(_texture_seed);

		return s_TextureRegistry[new_name];
	}
	void AssetManager::RegisterInternalTexture(std::string _path, std::string _name)
	{
		DataBlock::Image2D image_raw = Loader::TextureLoader::OELoadImage(_path);
		if (!image_raw.Valid)
			return;
		// make sure this image or at least another image with the same name
		bool name_exist = (s_TextureInternalRegistry.find(_name) != s_TextureInternalRegistry.end());
		if (name_exist)
		{
			return; // Just ignore it for now
		}

		s_TextureInternalRegistry.insert(std::make_pair(_name, new Texture(image_raw)));
	}
	void AssetManager::RegisterHDRITexture(std::string _path, std::string _name)
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
	Texture* AssetManager::GetInternalTexture(std::string _name)
	{
		if (auto iter = s_TextureInternalRegistry.find(_name) == s_TextureInternalRegistry.end())
			return nullptr;

		return s_TextureInternalRegistry[_name];
	}
	Texture* AssetManager::GetHDRITexture(std::string _name)
	{
		if (auto iter = s_TextureHDRIRegistry.find(_name) == s_TextureHDRIRegistry.end())
			return nullptr;

		return s_TextureHDRIRegistry[_name];
	}


	IVModel* AssetManager::GetGeometry(uint32_t _model_id)
	{
		if(s_RenderableGeometryIDTranslator.find(_model_id) == s_RenderableGeometryIDTranslator.end())
			return nullptr;
		return &s_RenderableGeometry[s_RenderableGeometryIDTranslator[_model_id]];
	}
	IVModel* AssetManager::GetGeometry(std::string _name)
	{
		if (s_RenderableGeometry.find(_name) == s_RenderableGeometry.end())
			return nullptr;
		return &s_RenderableGeometry[_name];
	}
	std::string AssetManager::RegisterGeometry(IVModel _model)
	{
		uint32_t model_id = _model.PackageID;
		std::string model_name = _model.Name;

		if (s_RenderableGeometry.find(model_name) != s_RenderableGeometry.end())
			model_name = Util::UtilFunc::CheckNameCollision(_model.Name, AssetManager::NameExist);

		s_RenderableGeometryIDTranslator.insert(std::make_pair(model_id, model_name));
		s_RenderableGeometry.insert(std::make_pair(model_name, _model));

		return model_name;
	}

	IVModel* AssetManager::GetGeometryI(DynamicAssetType _type)
	{
		if (s_InternalPurposeGeometry.find(_type) == s_InternalPurposeGeometry.end())
			return nullptr;
		return &s_InternalPurposeGeometry[_type];
	}
	void AssetManager::RegisterGeometryI(IVModel _model, DynamicAssetType _type)
	{
		if (s_InternalPurposeGeometry.find(_type) != s_InternalPurposeGeometry.end())
		{
			LOG_ERROR(LogLayer::Pipe("Dynamic Asset already exist!", OELog::WARNING));
			return;
		}
		s_InternalPurposeGeometry.insert(std::make_pair(_type, _model));
	}

	std::unordered_map<std::string, Texture*>& AssetManager::GetTextureRegistry()
	{
		return s_TextureRegistry;
	}
	std::unordered_map<std::string, Texture*>& AssetManager::GetTextureInternalRegistry()
	{
		return s_TextureInternalRegistry;
	}

	bool AssetManager::NameExistStaticGeo(std::string _name)
	{
		for (auto iter = s_RenderableGeometry.begin(); iter != s_RenderableGeometry.end(); iter++)
			if (iter->first == _name)
				return true;

		return false;
	}
	bool AssetManager::CheckTextureNameExist(std::string _name)
	{
		for (auto iter = s_TextureRegistry.begin(); iter != s_TextureRegistry.end(); iter++)
			if (iter->first == _name)
				return true;

		return false;
	}
	bool AssetManager::NameExist(std::string _name)
	{
		return NameExistStaticGeo(_name);
	}
	std::string AssetManager::CreateTextureSeed(DataBlock::Image2D& _image)
	{
		std::string _seed;
		// Define the number of samples per diagonal
		const int numSamples = 10;

		// Calculate the step size for sampling along each diagonal
		float stepX = static_cast<float>(_image.Width) / numSamples;
		float stepY = static_cast<float>(_image.Height) / numSamples;

		// Sample pixels along the diagonal from top-left to bottom-right
		for (int i = 0; i < numSamples; ++i) {
			int x = static_cast<int>(i * stepX);
			int y = static_cast<int>(i * stepY);

			// Calculate the index of the pixel
			int index = (y * _image.Width + x) * _image.Channel;

			// Read pixel values at the calculated index
			unsigned char* p = _image.Data + index;

			for (int c = 0; c < _image.Channel; ++c) {
				_seed.append(std::to_string(static_cast<unsigned int>(p[c])));
			}

			// Process the sampled pixel values here
		}
		_seed.append("<-X->");
		// Sample pixels along the diagonal from top-right to bottom-left
		for (int i = 0; i < numSamples; ++i) {
			int x = static_cast<int>(_image.Width - 1 - (i * stepX));
			int y = static_cast<int>(i * stepY);

			// Calculate the index of the pixel
			int index = (y * _image.Width + x) * _image.Channel;

			// Read pixel values at the calculated index
			unsigned char* p = _image.Data + index;

			for (int c = 0; c < _image.Channel; ++c) {
				_seed.append(std::to_string(static_cast<unsigned int>(p[c])));
			}
		}

		return _seed;
	}
}