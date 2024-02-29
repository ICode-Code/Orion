#ifndef OE1_LOADER_DEF_H_
#define OE1_LOADER_DEF_H_

#include "../Texture/TextureLoader.h" 
#include "../Util/DataBlock.h"
#include "../Util/LoaderUtil.h"
#include "../Util/LoadArgs.h"

#include <limits>
#include <unordered_map>
#include <map>

namespace OE1Core
{
	namespace Loader
	{
		struct TexturePkg
		{
			DataBlock::TextureType TexType;
			DataBlock::Image2D TexData;
		};

		using TextureSet = std::unordered_map<std::string, DataBlock::TextureType>;

		using DynamicMeshSet = std::unordered_map<int, std::tuple<std::string, std::vector<DataBlock::UnprocessedDynamicGeometry>>>;
		
		
		using MeshSet = std::unordered_map<int, std::tuple<std::string, std::vector<DataBlock::UnprocessedGeometry>>>;

		struct LoadPackage
		{
			std::unordered_map<int, std::tuple<std::string, std::vector<DataBlock::UnprocessedDynamicGeometry>>> SkinnedMeshSet;
			std::unordered_map<int, std::tuple<std::string, std::vector<DataBlock::UnprocessedGeometry>>> StaticMeshSet;
			std::map<std::string, DataBlock::BoneInfo> BoneInfoMap;
			int BoneCounter = 0;
			bool IsStaticMesh;
			bool HasValidData = false;
			LoadArgs LoadArg;
		};
	}
}

#endif // !OE1_LOADER_DEF_H_
