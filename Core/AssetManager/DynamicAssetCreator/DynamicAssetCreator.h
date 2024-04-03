#ifndef OE1_DYNAMIC_ASSET_CREATOR_H_
#define OE1_DYNAMIC_ASSET_CREATOR_H_


#include "../AssetManager/GeometryAssetPacketBuffer/GeometryAssetPacketBuffer.h"
#include "../Core/MeshCluster/IVModel.h"
#include "../Core/MeshCluster/StaticMeshInstancePkg.h"
#include "../Core/MeshCluster/CoreDebugShape.h"

namespace OE1Core
{
	namespace DAC
	{
		class GeometryCreator
		{
		public:
			GeometryCreator() = default;
			~GeometryCreator() = default;

			/// <summary>
			/// Mesh
			/// </summary>
			/// <returns></returns>
			static IVModel GetSphere();


			static IVModel GetDebugShapeAABB(CoreMeshDescriptor::MeshBound _bound);
			static IVModel GetDebugShapeAABB(glm::vec3 _min, glm::vec3 _max);


		private:
			static void InitGLBuffer(CoreRenderableMeshPackage& _core_mesh, bool _use_indices_buffer = true);
			static int GetPackageID();

		private:
			inline static int s_DynamicAssetID = 1;
		};
	}
}

#endif // !OE1_DYNAMIC_ASSET_CREATOR_H_
