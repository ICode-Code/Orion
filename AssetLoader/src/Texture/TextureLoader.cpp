#include "TextureLoader.h"

// STBI
#define STB_IMAGE_IMPLEMENTATION
#include <STBI/stb_image.h>




namespace OE1Core
{
	namespace Loader
	{
		TextureLoader::TextureLoader()
		{

		}
		TextureLoader::~TextureLoader()
		{

		}

		DataBlock::Image2D TextureLoader::OELoadImage(std::string _path)
		{
			DataBlock::Image2D image_data;
			image_data.Valid = false;

			/// Make sure the path is valid
			if (_path.empty())
			{
				LOG_ERROR("Faild to load image: Invalid Path: {0}", _path);
				return image_data;
			}

			image_data.Data = stbi_load(
				_path.c_str(),
				&image_data.Width,
				&image_data.Height,
				&image_data.Channel,
				4
			);

			if (!image_data.Data)
			{
				LOG_ERROR("Faild to load image: {0}", _path);
				return image_data;
			}

			image_data.Path = NameHandle::FilterPath(_path);
			image_data.Name = NameHandle::FilterFileName(_path);
			image_data.Valid = true;
			return image_data;

		}
		DataBlock::Image2D TextureLoader::OELoadImage(const aiTexture* _embd)
		{
			DataBlock::Image2D dest_image_data;
			dest_image_data.Valid = false;
			// Extract Image Data
			if (_embd->mHeight == 0)
				dest_image_data.Data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(_embd->pcData),
					_embd->mWidth, &dest_image_data.Width, &dest_image_data.Height, &dest_image_data.Channel, 4);
			else
				dest_image_data.Data = stbi_load_from_memory(reinterpret_cast<unsigned char*>(_embd->pcData),
					_embd->mWidth * _embd->mHeight, &dest_image_data.Width, &dest_image_data.Height, &dest_image_data.Channel, 4);

			if (!dest_image_data.Data)
			{
				LOG_ERROR("Faild to load embedded image: {0}", _embd->mFilename.C_Str());
				return dest_image_data;
			}

			dest_image_data.Path = NameHandle::FilterPath(std::string(_embd->mFilename.C_Str()));
			dest_image_data.Name = NameHandle::FilterFileName(_embd->mFilename.C_Str());
			dest_image_data.Valid = true;
			
			return dest_image_data;
		}
		DataBlock::Image2DArray TextureLoader::OELoadImage(std::vector<std::string> _paths)
		{
			DataBlock::Image2DArray image_list;
			DataBlock::Image2DArray image_list_temp;
			if (_paths.empty())
			{
				LOG_ERROR("Failed to load image list");
				return image_list;
			}

			for (size_t i = 0; i < _paths.size(); i++)
				image_list_temp.ImageDataArray.push_back(OELoadImage(_paths[i]));

			// Clip unloaded image
			for (size_t i = 0; i < _paths.size(); i++)
				if (image_list_temp.ImageDataArray[i].Valid)
					image_list.ImageDataArray.push_back(image_list_temp.ImageDataArray[i]);

			return image_list;
		}
		DataBlock::ImageHDRI TextureLoader::OELoadHDRI(std::string _path)
		{
			DataBlock::ImageHDRI image_hdri;

			if (_path.empty())
			{
				LOG_ERROR("Faild to load HDRI: Invalid Path: {0}", _path);
				return image_hdri;
			}

			stbi_set_flip_vertically_on_load(1);

			image_hdri.Data = stbi_loadf(
				_path.c_str(),
				&image_hdri.Width,
				&image_hdri.Height,
				&image_hdri.Channel,
				4
			);

			stbi_set_flip_vertically_on_load(1);

			if (!image_hdri.Data)
			{
				LOG_ERROR("Faild to load HDRI: Unsupported Image");
				return image_hdri;
			}

			image_hdri.Path = NameHandle::FilterPath(_path);
			image_hdri.Path = NameHandle::FilterFileName(_path);
			image_hdri.Valid = true;

			return image_hdri;
		}
	}
}