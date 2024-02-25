#include "IVLoader.h"

namespace OE1Core
{
	namespace Loader
	{
		void IVLoader::Import(LoadArgs _args)
		{

			Loader::LoadPackage _package =  CoreGeometryLoader::BeginLoad(_args);

			if (_package.IsStaticMesh && _package.HasValidData)
				Loader::IVLoadedAsset::s_StaticMeshAsset.push(_package);
			else if (!_package.IsStaticMesh && _package.HasValidData)
				Loader::IVLoadedAsset::s_SkinnedMeshAsset.push(_package);
			else
			{
				CoreGeometryLoader::PROGRESS_INFO = "Failed to import asset! " + _args.SourcePath;
				return;

			}

			// update info
			CoreGeometryLoader::PROGRESS_INFO = "Establishing Orion asset..";
		}
	}
}