#ifndef OE1_RESOURCE_INITIALIZER_H_
#define OE1_RESOURCE_INITIALIZER_H_

#include "AssetManager.h"
#include "DynamicAssetCreator/DynamicAssetCreator.h"

namespace OE1Core
{
	class ResourceInitializer
	{
	public:
		ResourceInitializer();
		~ResourceInitializer();


	private:
		void InitTexture();
		void InitBaseMesh();
		void InitInternalUsageMesh();


	private:
		inline static const std::string s_DefaultTexturePath = "../ExternalAsset/Default/Texture/";
		inline static const std::string s_DefaultMeshPath = "../ExternalAsset/Default/Mesh/";
	};
}

#endif // !OE1_RESOURCE_INITIALIZER_H_
