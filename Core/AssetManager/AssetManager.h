#ifndef OE1_ASSET_MANAGER_H_
#define OE1_ASSET_MANAGER_H_

#include "../Core/Texture/Texture.h"
#include "Texture/TextureLoader.h"
#include "../Core/MeshCluster/IVModel.h"
#include "DynamicAssetCreator/DynamicAssetType.h"

#include <unordered_map>

#include "UtilFunc/UtilFunc.h"

namespace OE1Core
{
	class AssetManager
	{
		friend class ContentBrowserLayer;
	public:
		AssetManager();
		~AssetManager();

		// make sure it is not nullptr before using
		static Texture* GetInternalTexture(std::string _name);

		// make sure it is not nullptr before using
		static Texture* GetTexture(std::string _name);
		// make sure it is not nullptr before using
		static Texture* GetHDRITexture(std::string _name);
		static void RegisterHDRITexture(std::string _path, std::string _name);

		static Texture* RegisterTexture(std::string _path, std::string _name);

		// This function call stbi_image_free(..) indirectly
		static Texture* RegisterTexture(DataBlock::Image2D& _image);

		static void RegisterInternalTexture(std::string _path, std::string _name);

		// Static Geometry

		static IVModel* GetGeometry(uint32_t _model_id);
		static IVModel* GetGeometry(std::string _name);
		static std::string RegisterGeometry(IVModel _model);

		// Internal Geometry
		static IVModel* GetGeometryI(DynamicAssetType _type);
		static void RegisterGeometryI(IVModel _model, DynamicAssetType _type);

		static std::unordered_map<std::string, Texture*>& GetTextureRegistry();
		static std::unordered_map<std::string, Texture*>& GetTextureInternalRegistry();

		


	protected:
		inline static std::unordered_map<std::string, Texture*> s_TextureRegistry;
		inline static std::unordered_map<std::string, Texture*> s_TextureHDRIRegistry;

		inline static std::unordered_map<std::string, IVModel> s_RenderableGeometry;
		inline static std::unordered_map<uint32_t, std::string> s_RenderableGeometryIDTranslator;

		inline static std::unordered_map<DynamicAssetType, IVModel> s_InternalPurposeGeometry;

		inline static std::unordered_map<std::string, Texture*> s_TextureInternalRegistry;


	private: // Util function
		static bool NameExistStaticGeo(std::string _name);
		static bool NameExist(std::string _name);
	};
}

#endif // !OE1_ASSET_MANAGER_H_
