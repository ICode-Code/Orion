#include "ResourceInitializer.h"
#include "../AssetManager/AssetParser/AssetParser.h"
#include <iostream>

namespace OE1Core
{
	ResourceInitializer::ResourceInitializer()
	{
		LOG_WARRNING("Loading Textures..");
		InitTexture();
		LoadDefaultCubeMap();
		InitBaseMesh();
		InitInternalUsageMesh();
	}
	ResourceInitializer::~ResourceInitializer()
	{

	}

	void ResourceInitializer::InitTexture()
	{
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Folder.png",				"Folder");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Question.png",			"Question");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Play.png",				"Play");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Unknown.png",				"Unknown");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "wav.png",					"Wav");

		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PointLight.png",			"PointLight");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Sun.png",					"Sun");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "SpotLight.png",			"SpotLight");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Camera.png",				"Camera");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Scene.png",				"SceneIco");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "AudioSource.png",			"AudioSource");

		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "EmptyProject.png",		"EmptyProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "FPSTestProject.png",		"FPSTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PBRTestProject.png",		"PBRTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Pose.png",				"Pose");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "ibl_brdf_lut.png",		 "LUT");

	}
	void ResourceInitializer::LoadDefaultCubeMap()
	{
		if(!std::filesystem::exists(s_DefaultCubemapTexturePath))
			return;
		for (auto& data_iter : std::filesystem::directory_iterator(s_DefaultCubemapTexturePath))
		{
			if (data_iter.is_directory())
			{
				std::string _name = data_iter.path().stem().string();
				std::vector<DataBlock::Image2D> _cube_source;
				for (auto& tex_iter : std::filesystem::directory_iterator(data_iter))
					_cube_source.push_back(Loader::TextureLoader::OELoadImage(tex_iter.path().string()));
				

				CommandDef::CreateSkyboxInitCommandDef _commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));
				_commandX.Sources = _cube_source;
				_commandX.Name = _name;

				Command::PushSkyBoxInitCommand(_commandX);
				//AssetManager::RegisterTextureCubeMap(_cube_source, _name);
			}
		}

		// Light 
		for (auto& file_iter : std::filesystem::directory_iterator(s_DefaultEnvironmentTexturePath))
		{
			std::string _ext = file_iter.path().extension().string();

			if (_ext == ".hdr")
			{
				std::string _path = file_iter.path().string();
				std::string _name = file_iter.path().stem().string();

				CommandDef::CreateSceneLightRoomCommandDef _commandX(ORI_COMMAND_DEF_ARGS(__FUNCTION__));

				_commandX.Name = _name;
				_commandX.Path = _path;

				Command::PushSceneInitiCommand(_commandX);

			}
		}


	}
	void ResourceInitializer::InitBaseMesh()
	{

	}
	void ResourceInitializer::InitInternalUsageMesh()
	{
		AssetManager::RegisterGeometryI(DAC::GeometryCreator::GetSphere(), DynamicAssetType::SPHERE);

		/*Loader::StaticGeometryLoader::MeshSet mesh;
		Loader::StaticGeometryLoader::OELoadStaticGeometry(s_DefaultMeshPath + "Sphere.fbx", mesh);
		
		AssetParser::ParseStaticGeometryI(mesh, DynamicAssetType::SPHERE);*/

	}
}