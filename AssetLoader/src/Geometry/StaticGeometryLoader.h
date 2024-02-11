#ifndef OE1_STATIC_GEOMETRY_LOADER_H_
#define OE1_STATIC_GEOMETRY_LOADER_H_


#include "../Texture/TextureLoader.h" // Load texture
#include "../Util/DataBlock.h"
#include "../Util/LoaderUtil.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <limits>
#include <unordered_map>

namespace OE1Core
{
	namespace Loader
	{
		struct TexturePkg
		{
			DataBlock::TextureType TexType;
			DataBlock::Image2D TexData;
		};
		class StaticGeometryLoader
		{
		public:
			StaticGeometryLoader();
			~StaticGeometryLoader();

			using MeshSet = std::unordered_map<int, std::tuple<std::string, std::vector<DataBlock::UnprocessedGeometry>>>;
			using TextureSet = std::unordered_map<std::string, DataBlock::TextureType>;
			static void OELoadStaticGeometry(std::string _path, MeshSet& _mesh_set, std::unordered_map<std::string, TexturePkg>& _tex_buffer);

			// load Progress
			inline static float PROGRESS_LEVEL = 0.0f;
			inline static std::string PROGRESS_INFO = "";

		protected:
			inline static const aiScene* s_Scene = nullptr;
			inline static Assimp::Importer s_Importer;
			inline static std::string s_AbsPath;

			/// Don't touch
			inline static int s_MeshGroupID = 0;

		protected: // internal
			static bool LoadToMemory(std::string _path);
			static void ExtractScene(aiNode* _node, MeshSet& _mesh_set);
			static DataBlock::UnprocessedGeometry GetSingleMesh(aiMesh* _mesh_node);
			static TextureSet GetTextureSet(aiMaterial* _material);
			static void RegisterSingleTexture(TextureSet& _texture_set, DataBlock::TextureType _oe_texture_type, aiTextureType _ai_texture_type, aiMaterial* _material);
			static DataBlock::Image2D ReadTextureData(std::string _path);
			static std::string GetTextureName(std::string _path);

		private: // Texture buffer
			inline static std::unordered_map<std::string, TexturePkg> s_LoadedTexture;
			static bool IsTextureAlreadyLoaded(std::string _name);
			/// <summary>
			/// Make sure the texture exist before query
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static TexturePkg GetLoadedTexture(std::string _name);
			static void RegisterTexture(std::string _name, DataBlock::TextureType _type, DataBlock::Image2D _image);
			inline static std::unordered_map<std::string, DataBlock::TextureType> s_TextureSignature;

		};
	}
}

#endif // !OE1_STATIC_GEOMETRY_LOADER_H_
