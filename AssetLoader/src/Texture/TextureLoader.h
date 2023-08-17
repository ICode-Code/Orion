#ifndef OE1_TEXTURE_LOADER_H_
#define OE1_TEXTURE_LOADER_H_

#include <string>
#include <assimp/scene.h>

#include <Log.h>
#include "../Util/DataBlock.h"
#include "../Util/NameHandle.h"

namespace OE1Core
{
	namespace Loader
	{
		class TextureLoader
		{
		public:
			TextureLoader();
			~TextureLoader();


			/// <summary>
			/// Used to load image in png, jpeg or any other that STBI image loader support 
			/// but NOT HDRI
			/// The Caller must call ->"stbi_image_free()" after loading
			/// make the path file is separated by single back slash '/'
			/// </summary>
			/// <param name="image">Image Path</param>
			/// <returns>Image Data</returns>
			static DataBlock::Image2D OELoadImage(std::string _path);
			static DataBlock::Image2D OELoadImage(const aiTexture* _embd);
			static DataBlock::Image2DArray OELoadImage(std::vector<std::string> _paths);
			/// <summary>
			/// load HDRI image
			/// The Caller must call ->"stbi_image_free()" after loading
			/// </summary>
			/// <param name="path">Image Path</param>
			/// <returns>Image Data</returns>
			static DataBlock::ImageHDRI OELoadHDRI(std::string _path);
		};
	}
}

#endif // !OE1_TEXTURE_LOADER_H_
