#ifndef OE1_ASSET_PARSER_H_
#define OE1_ASSET_PARSER_H_

#include "ShaderGenerator/ShaderGenerator.h"
#include "../../Common/Shared/AvailTexture.h"
#include "../../Common/Shared/PreDef.h"
#include "../AssetManager.h"
#include "Geometry/GeometryLoader.h"
#include "../../Core/MeshCluster/ModelPkg.h"
#include "../../Core/MeshCluster/StaticMeshInstancePkg.h"

namespace OE1Core
{
	class AssetParser
	{
	public:
		AssetParser() = default;
		~AssetParser() = default;
		
		// This function need to be called with the thread with active OpenGL context
		static void ParseStaticGeometry(Loader::StaticGeometryLoader::MeshSet& _mesh_set);
		static void ParseDynamicGeometry();


	protected:
		static void Texture2DFilter();
		static uint32_t CreateMaterial(Loader::StaticGeometryLoader::TextureSet& _texture);
		static void BufferIntilization(CoreStaticMeshPkg& _core_mesh);
		static CoreStaticMeshPkg ProcessGeometry(DataBlock::UnprocessedGeometry& _unprocessed_geometry, uint32_t _package_id, bool _load_mat = true);
		static uint32_t GetAssetID();

	private:
		inline static uint32_t s_ASSET_ID = 0;
		inline static AvailTexture s_AvialTextures;
	};
}

#endif // !OE1_ASSET_PARSER_H_
