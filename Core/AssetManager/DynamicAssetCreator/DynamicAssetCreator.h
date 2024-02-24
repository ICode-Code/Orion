#ifndef OE1_DYNAMIC_ASSET_CREATOR_H_
#define OE1_DYNAMIC_ASSET_CREATOR_H_


#include "../AssetManager/GeometryAssetPacketBuffer/GeometryAssetPacketBuffer.h"
#include "../Core/MeshCluster/IVModel.h"
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


			static IVModel GetSphere();


		private:
			static void InitGLBuffer(CoreRenderableMeshPackage& _core_mesh);
			static int GetPackageID();

		private:
			inline static int s_DynamicAssetID = 1;
		};
	}
}

#endif // !OE1_DYNAMIC_ASSET_CREATOR_H_
