#include "ResourceInitializer.h"
#include <Geometry/StaticGeometryLoader.h>
#include "../AssetManager/AssetParser/AssetParser.h"

namespace OE1Core
{
	ResourceInitializer::ResourceInitializer()
	{
		InitTexture();
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
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Camera.png",				"Camera");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "Scene.png",				"SceneIco");

		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "EmptyProject.png",		"EmptyProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "FPSTestProject.png",		"FPSTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PBRTestProject.png",		"PBRTestProject");
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