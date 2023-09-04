#ifndef OE1_ASSET_MANAGER_H_
#define OE1_ASSET_MANAGER_H_

#include "../Core/Texture/Texture.h"
#include "Texture/TextureLoader.h"

#include <unordered_map>

namespace OE1Core
{
	class AssetManager
	{
	public:
		AssetManager();
		~AssetManager();

		// make sure it is not nullptr before using
		static Texture* GetTexture(std::string _name);
		// make sure it is not nullptr before using
		static Texture* GetTextureHDRI(std::string _name);
		static void RegisterHDRIImage(std::string _path, std::string _name);
		static void RegisterImage(std::string _path, std::string _name);


	protected:
		inline static std::unordered_map<std::string, Texture*> s_TextureRegistry;
		inline static std::unordered_map<std::string, Texture*> s_TextureHDRIRegistry;

	};
}

#endif // !OE1_ASSET_MANAGER_H_
