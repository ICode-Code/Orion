#include "ResourceInitializer.h"


namespace OE1Core
{
	ResourceInitializer::ResourceInitializer()
	{
		InitTexture();
		InitBaseMesh();
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
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "EmptyProject.png",		"EmptyProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "FPSTestProject.png",		"FPSTestProject");
		AssetManager::RegisterInternalTexture(s_DefaultTexturePath + "PBRTestProject.png",		"PBRTestProject");
	}
	void ResourceInitializer::InitBaseMesh()
	{

	}
}