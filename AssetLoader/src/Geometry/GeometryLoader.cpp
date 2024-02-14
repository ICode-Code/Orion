#include "GeometryLoader.h"


namespace OE1Core
{
	namespace Loader
	{
		using namespace std::chrono_literals;
		void GeometryLoader::LoadGeometry(LoadArgs _load_args)
		{

			// _is_running: is specific to this function so if we need some global info
			s_Working = true;

			// Init
			LoadAssetPkg AssetPackage;
			AssetPackage.Args = _load_args;

			// heavy process
			StaticGeometryLoader::OELoadStaticGeometry(_load_args.SourcePath, AssetPackage.MeshSet, AssetPackage.TextureBuffer);


			// to the list
			s_MeshSets.push(AssetPackage);

			// update info
			StaticGeometryLoader::PROGRESS_INFO = "Establishing Orion asset..";
		}
	}
}