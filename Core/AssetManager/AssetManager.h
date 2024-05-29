#ifndef OE1_ASSET_MANAGER_H_
#define OE1_ASSET_MANAGER_H_

#include "Animation/Animation.h"
#include "../Core/Texture/Texture.h"
#include "../Core/Texture/TextureCubeMap.h"
#include "Texture/TextureLoader.h"
#include "../Core/MeshCluster/IVModel.h"
#include "../Core/MeshCluster/CoreDebugShape.h"
#include "DynamicAssetCreator/DynamicAssetType.h"

#include <unordered_map>

#include "UtilFunc/UtilFunc.h"

namespace OE1Core
{
	class AssetManager
	{
		friend class ContentBrowserLayer;
		friend class AnimationStateMachinePad;
	public:
		AssetManager();
		~AssetManager();

		// make sure it is not nullptr before using
		static Texture* GetInternalTexture(std::string _name);

		static TextureCubeMap* GetCubeMapTexture(std::string _name);
		static std::unordered_map<std::string, TextureCubeMap*>& GetCubeMapTextureRegistry();
		static void RegisterTextureCubeMap(std::vector<DataBlock::Image2D> _source, std::string _image);

		static bool HasTexture(std::string _name);
		static bool HasTexture(DataBlock::Image2D& _image);
		// make sure it is not nullptr before using
		static Texture* GetTexture(std::string _name);
		// make sure it is not nullptr before using
		static Texture* GetHDRITexture(std::string _name);
		static void RegisterHDRITexture(std::string _path, std::string _name);

		static Texture* RegisterTexture(std::string _path, std::string _name);

		// This function call stbi_image_free(..) indirectly
		static Texture* RegisterTexture(DataBlock::Image2D& _image);

		static void RegisterInternalTexture(std::string _path, std::string _name);

		// Animation
		static Animation* GetAnimation(std::string _name);
		static std::string RegisterAnimation(Animation* _animation);
		static std::vector<std::string> RegisterAnimation(std::vector<Animation*> _animations);
		static std::unordered_map<std::string, Animation*>& GetAnimationRegistry();

		// Geometry
		static IVModel* GetGeometry(uint32_t _model_id);
		static IVModel* GetGeometry(std::string _name);
		static std::string RegisterGeometry(IVModel _model);

		// Internal Geometry
		static IVModel* GetGeometryI(DynamicAssetType _type);
		static void RegisterGeometryI(IVModel _model, DynamicAssetType _type);

		// Debug Mesh

		static std::unordered_map<std::string, IVModel>& GetDebugMeshRegistry();
		static bool RegisterDebugMesh(std::string _name, IVModel _model);
		static IVModel* GetDebugMesh(std::string _id);


		static std::unordered_map<std::string, Texture*>& GetTextureRegistry();
		static std::unordered_map<std::string, Texture*>& GetTextureInternalRegistry();

		


	protected:
		inline static std::unordered_map<std::string, Texture*> s_TextureRegistry;
		inline static std::unordered_map<std::string, Texture*> s_TextureHDRIRegistry;

		inline static std::unordered_map<std::string, IVModel> s_RenderableGeometry;
		inline static std::unordered_map<uint32_t, std::string> s_RenderableGeometryIDTranslator;

		inline static std::unordered_map<DynamicAssetType, IVModel> s_InternalPurposeGeometry;

		inline static std::unordered_map<std::string, Texture*> s_TextureInternalRegistry;
		inline static std::unordered_map<std::string, TextureCubeMap*> s_TextureCubeMapInternalRegistry;

		inline static std::unordered_map<std::string, IVModel> s_DebugMeshRegistry;

		// any Loaded Animation
		inline static std::unordered_map<std::string, Animation*> s_AnimationRegistry;


	private: // Util function
		static bool NameExistStaticGeo(std::string _name);
		static bool NameExist(std::string _name);
		static bool CheckTextureNameExist(std::string _name);
	};
}

#endif // !OE1_ASSET_MANAGER_H_
