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
		AssetManager::RegisterImage(s_DefaultTexturePath + "Folder.png",		"Folder");
		AssetManager::RegisterImage(s_DefaultTexturePath + "Question.png",		"Question");
		AssetManager::RegisterImage(s_DefaultTexturePath + "Play.png",			"Play");
		AssetManager::RegisterImage(s_DefaultTexturePath + "Unknown.png",		"Unknown");
	}
	void ResourceInitializer::InitBaseMesh()
	{

	}
}