#ifndef OE1_ASSET_PARSER_H_
#define OE1_ASSET_PARSER_H_

#include "ShaderGenerator/ShaderGenerator.h"
#include "../../Core/Material/MaterialManager.h"
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
		static std::vector<std::string> ParseStaticGeometry(Loader::StaticGeometryLoader::MeshSet& _mesh_set, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer);
		//static std::vector<std::string> ParseStaticGeometryI(Loader::StaticGeometryLoader::MeshSet& _mesh_set, DynamicAssetType _type);
		static void ParseDynamicGeometry();


	protected:
		static void ReadModelInfo(ModelPkg& model_package);
		static void ReadTextureData(DataBlock::Image2D& _image, int _layer, std::string _mat_name);
		static void Texture2DFilter();
		static void CreateMaterial(Loader::StaticGeometryLoader::TextureSet& _textures, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer, std::string _name, uint32_t _local_id, uint32_t _pkg_id);
		static void BufferIntilization(CoreStaticMeshPkg& _core_mesh);
		static CoreStaticMeshPkg ProcessGeometry(DataBlock::UnprocessedGeometry& _unprocessed_geometry, std::unordered_map<std::string, Loader::TexturePkg>& _texture_buffer, uint32_t _package_id, uint32_t _local_id, bool _load_mat = true);
		static void PreProcessGeometry(std::vector<DataBlock::UnprocessedGeometry>& _unprocessed_geometry);
		static uint32_t GetAssetID();
		static bool FetchTexture(std::string _name, DataBlock::TextureType _type, std::unordered_map<std::string, Loader::TexturePkg>& _buffer, std::unordered_map<DataBlock::TextureType, DataBlock::Image2D>& _dest);
		static bool HasTexture(DataBlock::TextureType _type, Loader::StaticGeometryLoader::TextureSet& _buff);
		static std::string GetTextureName(DataBlock::TextureType _type, Loader::StaticGeometryLoader::TextureSet& _buff);
	private:
		inline static uint32_t s_ASSET_ID = 0;
		inline static AvailTexture s_AvialTextures;
	};
}

#endif // !OE1_ASSET_PARSER_H_
