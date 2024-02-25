#ifndef OE1_LOADED_ASSET_H_
#define OE1_LOADED_ASSET_H_

#include <queue>
#include <unordered_map>
#include <functional>
#include "../Geometry/LoaderDef.h"


namespace OE1Core
{
	namespace Loader
	{
		class IVLoadedAsset
		{
		public:
			IVLoadedAsset() = delete;
			~IVLoadedAsset() = delete;

			inline static std::queue<Loader::LoadPackage> s_StaticMeshAsset;
			inline static std::queue<Loader::LoadPackage> s_SkinnedMeshAsset;
			inline static std::unordered_map<std::string, Loader::TexturePkg> s_Textures;

		public:
			static bool IsTextueLoaded(std::string _name);
			static bool IsTextueLoaded(DataBlock::Image2D& _image);

			inline static int s_TotalRegistedTexture = 0;
			inline static int s_TotalRelaesedTexture = 0;


			static void FreeUnusedTexture();
			/// <summary>
			/// Make sure the texture exist before trying to add ref count
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static bool IncreaseTextureRefCount(std::string _name);

			/// <summary>
			/// When the ref count reach zero the texture will be deleted
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static bool DecreaseTextureRefCount(std::string _name);

			/// <summary>
			/// This might modefy texture name and return that name 
			/// watch out for that if d/t texture with the same name loaded
			/// the send texture will have (n)
			/// </summary>
			/// <param name="_image"></param>
			static std::string RegisterTexture(std::string _name, Loader::TexturePkg _image_pkg);
			/// <summary>
			/// This does not check weather the texture exist or not so
			/// check before tryng to retraive
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static DataBlock::Image2D* GetTextureData(std::string _name);
			/// <summary>
			/// This does not check weather the texture exist or not so
			/// check before tryng to retraive
			/// </summary>
			/// <param name="_name"></param>
			/// <returns></returns>
			static DataBlock::TextureType GetTextureType(std::string _name);

			static bool CheckTextureNameExist(std::string _name);

			static std::string CreateTextureSeed(DataBlock::Image2D& _image);

			static std::string CheckNameCollision(std::string _name, std::function<bool(std::string)> _cmp);
		};
	}
}

#endif // !OE1_LOADED_ASSET_H_
