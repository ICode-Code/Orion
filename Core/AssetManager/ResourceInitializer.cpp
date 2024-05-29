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

		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PointLight.png",			"PointLight");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Sun.png",					"Sun");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "SpotLight.png",			"SpotLight");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Camera.png",				"Camera");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Scene.png",				"SceneIco");

		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "EmptyProject.png",		"EmptyProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "FPSTestProject.png",		"FPSTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PBRTestProject.png",		"PBRTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Pose.png",				"Pose");

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

				AssetManager::RegisterTextureCubeMap(_cube_source, _name);
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