#ifndef OE1_ASSET_MANAGER_H_
#define OE1_ASSET_MANAGER_H_

#include "../Core/Texture/Texture.h"
#include "Texture/TextureLoader.h"
#include "../Core/MeshCluster/ModelPkg.h"

#include <unordered_map>

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

		static void RegisterTexture(std::string _path, std::string _name);

		// This function call stbi_image_free(..) indirectly
		static void RegisterTexture(DataBlock::Image2D& _image);

		static void RegisterInternalTexture(std::string _path, std::string _name);

		static ModelPkg* GetGeometry(uint32_t _model_id);
		static ModelPkg* GetGeometry(std::string _name);
		static void RegisterGeometry(ModelPkg _model);

		// Internal Geometry
		static ModelPkg* GetGeometryI(uint32_t _model_id);
		static ModelPkg* GetGeometryI(std::string _name);
		static void RegisterGeometryI(ModelPkg _model);

		static std::unordered_map<std::string, Texture*>& GetTextureRegistry();
		static std::unordered_map<std::string, Texture*>& GetTextureInternalRegistry();

		


	protected:
		inline static std::unordered_map<std::string, Texture*> s_TextureRegistry;
		inline static std::unordered_map<std::string, Texture*> s_TextureHDRIRegistry;

		inline static std::unordered_map<std::string, ModelPkg> s_RenderableGeometry;
		inline static std::unordered_map<uint32_t, std::string> s_RenderableGeometryIDTranslator;

		inline static std::unordered_map<std::string, ModelPkg> s_InternalPurposeGeometry;
		inline static std::unordered_map<uint32_t, std::string> s_InternalPurposeGeometryIDTranslator;

		inline static std::unordered_map<std::string, Texture*> s_TextureInternalRegistry;
	};
}

#endif // !OE1_ASSET_MANAGER_H_
