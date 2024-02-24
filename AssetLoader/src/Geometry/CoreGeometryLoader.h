#ifndef OE1_CORE_GEOMETRY_LOADER_H_
#define OE1_CORE_GEOMETRY_LOADER_H_


#include "LoaderDef.h"
#include "../Util/LoadArgs.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <functional>
#include <string>

namespace OE1Core
{
	namespace Loader
	{
		using TextureLoadCheckCallback = std::function<bool(std::string)>;
		class CoreGeometryLoader
		{
		public:
			CoreGeometryLoader() = delete;
			~CoreGeometryLoader() = delete;

			// Do this once before start loading asset
			static void SetTextureCheckCallback(TextureLoadCheckCallback _callback);


			static LoadPackage BeginLoad(LoadArgs _args);




		private:
			static std::string GetTextureName(std::string _path);
			static bool LoadToMemory(std::string _path);
			static void ExtractStaticScene(aiNode* _node, LoadPackage& _package);
			static void ExtractDynamicScene(aiNode* _node, LoadPackage& _package);
			static void RegisterSingleTexture(
				TextureSet& _texture_set, 
				DataBlock::TextureType _oe_texture_type, 
				aiTextureType _ai_texture_type, 
				aiMaterial* _material,
				std::unordered_map<std::string, TexturePkg>& _textures_buffer);
			static TextureSet GetTextureSet(aiMaterial* _material, std::unordered_map<std::string, TexturePkg>& _textures_buffer);
			static DataBlock::UnprocessedGeometry GetSingleMesh(aiMesh* _mesh_node, std::unordered_map<std::string, TexturePkg>& _textures_buffer);
			static DataBlock::UnprocessedDynamicGeometry CollectSingleMeshBone(aiMesh* _mesh, DataBlock::UnprocessedGeometry& _geom, LoadPackage& _package);
			static DataBlock::Image2D ReadTextureData(std::string _path);

			/// <summary>
			/// When we load new texture we sign it so we don't have to
			/// load it again
			/// </summary>
			/// <param name="_name"></param>
			/// <param name="_type"></param>
			static void SignTexture(std::string _name, DataBlock::TextureType _type);

		private: // Util data

			/// <summary>
			/// This is a buffer hold temp textures for a given mesh, when loading a Model 
			/// we store the loaded texture here, so we don't have to load it twise for any related sub mesh
			/// and we clean it after loading a model, It will become the main thread propblem after this
			/// sicen unique textures are queued and loaded to the asset after that we can use the callback to avoid
			/// duplicate texture load, but this will save us from loading the same texture for a single model
			/// this happen when d/t sub mesh of the same model use the same material
			/// </summary>
			inline static std::unordered_map<std::string, DataBlock::TextureType> s_TextureSignature;
			/// <summary>
			/// helper to s_TextureSignature
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static bool IsTextureAlreadyLoaded(std::string _name);
			/// Don't touch
			inline static int s_MeshGroupID = 0;

			inline static bool s_SceneContainAnimation = false;

			inline static LoadArgs s_LoadArgument;

		private: // Utility functions
			static bool HasBoneStructure(aiNode* _node);

		private:
			inline static const aiScene* s_Scene = nullptr;
			inline static Assimp::Importer s_Importer;
			inline static std::string s_AbsPath;

		private: // Utilti callbacks

			inline static TextureLoadCheckCallback TextureLoaded;

		public: // Progress Tracker

			inline static float PROGRESS_LEVEL = 0.0f;
			inline static std::string PROGRESS_INFO = "";
		};
	}
}

#endif // !OE1_CORE_GEOMETRY_LOADER_H_
