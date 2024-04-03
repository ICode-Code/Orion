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
		
		for (auto iter : s_AnimationRegistry)
			delete iter.second;
		s_AnimationRegistry.clear();
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

		if (!_image.Valid || !_image.Data)
			return nullptr;
		
		// make sure this image or at least another image with the same name
		bool name_exist = (s_TextureRegistry.find(_name) != s_TextureRegistry.end());
		if (name_exist)
		{
			// Check seed
			if (s_TextureRegistry[_name]->GetSeed() == _image.Seed)
			{
				LOG_WARRNING(LogLayer::Pipe("Identical Image Detected! : [" + _name + "].", OELog::WARNING));

				return s_TextureRegistry[_name];
			}
		}
		// if it reach here the new image is truly new
		// Handle name 
		std::string new_name = Util::UtilFunc::CheckNameCollision(_name, AssetManager::CheckTextureNameExist);

		_image.Name = new_name;
		s_TextureRegistry.insert(std::make_pair(new_name, new Texture(_image)));

		// Set Seed
		s_TextureRegistry[new_name]->SetSeed(_image.Seed);

		return s_TextureRegistry[new_name];
	}
	bool AssetManager::HasTexture(std::string _name)
	{
		return s_TextureRegistry.find(_name) != s_TextureRegistry.end();
	}
	bool AssetManager::HasTexture(DataBlock::Image2D& _image)
	{
		if (!HasTexture(_image.Name))
			return false;

		return _image.Seed == s_TextureRegistry[_image.Name]->GetSeed();
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


	Animation* AssetManager::GetAnimation(std::string _name)
	{
		if (s_AnimationRegistry.find(_name) == s_AnimationRegistry.end())
			return nullptr;

		return s_AnimationRegistry[_name];
	}
	std::string AssetManager::RegisterAnimation(Animation* _animation)
	{
		if (s_AnimationRegistry.find(_animation->GetName()) != s_AnimationRegistry.end())
			return std::string();
		_animation->UpdateTransform(.001f);
		s_AnimationRegistry.insert(std::make_pair(_animation->GetName(), _animation));
		return _animation->GetName();
	}
	std::vector<std::string> AssetManager::RegisterAnimation(std::vector<Animation*> _animations)
	{
		std::vector<std::string> _return_list;
		std::vector<size_t> _ignore_idx;
		for (size_t i = 0; i < _animations.size(); i++)
			if (s_AnimationRegistry.find(_animations[i]->GetName()) != s_AnimationRegistry.end())
				_ignore_idx.push_back(i);

		if (_ignore_idx.size() == _animations.size())
			return _return_list;

		for (size_t i = 0; i < _animations.size(); i++)
		{
			bool _ignore = false;
			for (size_t j = 0; j < _ignore_idx.size(); j++)
				if (_ignore_idx[j] == i)
					_ignore = true;

			if (!_ignore)
			{
				s_AnimationRegistry.insert(std::make_pair(_animations[i]->GetName(), _animations[i]));
				_return_list.push_back(_animations[i]->GetName());
			}
		}

		return _return_list;
	}
	std::unordered_map<std::string, Animation*>&  AssetManager::GetAnimationRegistry()
	{
		return s_AnimationRegistry;
	}


	// Debug Shapes
	std::unordered_map<std::string, IVModel>& AssetManager::GetDebugMeshRegistry()
	{
		return s_DebugMeshRegistry;
	}
	bool AssetManager::RegisterDebugMesh(std::string _name, IVModel _mesh)
	{
		if (s_DebugMeshRegistry.find(_name) != s_DebugMeshRegistry.end())
			return false;

		s_DebugMeshRegistry.insert(std::make_pair(_name, _mesh));
		return true;
	}
	IVModel* AssetManager::GetDebugMesh(std::string _name)
	{
		if (s_DebugMeshRegistry.find(_name) == s_DebugMeshRegistry.end())
			return nullptr;
		
		return &s_DebugMeshRegistry[_name];
	}

}