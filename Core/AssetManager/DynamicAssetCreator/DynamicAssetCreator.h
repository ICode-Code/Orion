#ifndef OE1_DYNAMIC_ASSET_CREATOR_H_
#define OE1_DYNAMIC_ASSET_CREATOR_H_

#include "../Core/MeshCluster/ModelPkg.h"
#include "../Core/MeshCluster/StaticMeshInstancePkg.h"

namespace OE1Core
{
	namespace DAC
	{
		class GeometryCreator
		{
		public:
			GeometryCreator() = default;
			~GeometryCreator() = default;


			static ModelPkg GetSphere();


		private:
			static void InitGLBuffer(CoreStaticMeshPkg& _core_mesh);
			static int GetPackageID();

		private:
			inline static int s_DynamicAssetID = 1;
		};
	}
}

#endif // !OE1_DYNAMIC_ASSET_CREATOR_H_
