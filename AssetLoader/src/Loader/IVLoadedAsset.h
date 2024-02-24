#ifndef OE1_LOADED_ASSET_H_
#define OE1_LOADED_ASSET_H_

#include <queue>
#include "../Geometry/LoaderDef.h"


namespace OE1Core
{
	namespace Loader
	{
		class IVLoadedAsset
		{
		public:
			IVLoadedAsset() = delete;
			~IVLoadedAsset() = delete;

			inline static std::queue<Loader::LoadPackage> s_StaticMeshAsset;
			inline static std::queue<Loader::LoadPackage> s_SkinnedMeshAsset;
		};
	}
}

#endif // !OE1_LOADED_ASSET_H_
