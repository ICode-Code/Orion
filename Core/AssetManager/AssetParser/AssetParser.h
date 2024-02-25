#ifndef OE1_ASSET_PARSER_H_
#define OE1_ASSET_PARSER_H_


#include "../GeometryAssetPacketBuffer/GeometryAssetPacketBuffer.h"
#include "ShaderGenerator/ShaderGenerator.h"
#include "../../Core/Material/MaterialManager.h"
#include "../../Common/Shared/AvailTexture.h"
#include "../../Common/Shared/PreDef.h"
#include "../AssetManager.h"
#include "Geometry/CoreGeometryLoader.h"
#include "../../Core/MeshCluster/IVModel.h"
#include "../../Core/MeshCluster/StaticMeshInstancePkg.h"
#include "../../Core/MeshCluster/DynamicMeshInstancePkg.h"

namespace OE1Core
{
	class AssetParser
	{
	public:
		AssetParser() = default;
		~AssetParser() = default;
		
		// This function need to be called with the thread with active OpenGL context
		static std::vector<std::string> ParseStaticGeometry(Loader::MeshSet& _mesh_set);
		// This function need to be called with the thread with active OpenGL context
		static std::vector<std::string> ParseDynamicGeometry(Loader::DynamicMeshSet& _mesh_set);


	protected:
		static void ReadModelInfo(IVModel& model_package);
		static void ReadTextureData(DataBlock::Image2D& _image, int _layer, std::string _mat_name);
		static void Texture2DFilter();
		static void CreateMaterial(Loader::TextureSet& _textures, std::string _name, uint32_t _local_id, uint32_t _pkg_id);
		
		
		static void StaticMeshBufferIntilization(CoreRenderableMeshPackage& _core_mesh);
		static void SkinnedMeshBufferIntilization(CoreRenderableMeshPackage& _core_mesh);
		
		
		static CoreRenderableMeshPackage ProcessGeometry(DataBlock::UnprocessedGeometry& _unprocessed_geometry, uint32_t _package_id, uint32_t _local_id, bool _load_mat = true);
		static CoreRenderableMeshPackage ProcessGeometry(DataBlock::UnprocessedDynamicGeometry& _unprocessed_geometry, uint32_t _package_id, uint32_t _local_id, bool _load_mat = true);
		
		
		
		static void PreProcessGeometry(std::vector<DataBlock::UnprocessedGeometry>& _unprocessed_geometry);
		static uint32_t GetAssetID();
		static bool FetchTexture(std::string _name, DataBlock::TextureType _type, std::unordered_map<std::string, Loader::TexturePkg>& _buffer, std::unordered_map<DataBlock::TextureType, DataBlock::Image2D>& _dest);
		static bool HasTexture(DataBlock::TextureType _type, Loader::TextureSet& _buff);
		static std::string GetTextureName(DataBlock::TextureType _type, Loader::TextureSet& _buff);
	private:
		inline static uint32_t s_ASSET_ID = 0;
		inline static AvailTexture s_AvialTextures;


	private: // Util
		inline static std::unordered_map<std::string, DataBlock::TextureType> s_MappedTexture;
		static bool IsTextureAlreadyMapped(std::string _name);
	};
}

#endif // !OE1_ASSET_PARSER_H_
