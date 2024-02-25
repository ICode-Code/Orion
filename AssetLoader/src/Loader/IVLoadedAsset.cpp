#include "IVLoadedAsset.h"
#include <STBI/stb_image.h>

namespace OE1Core
{
	namespace Loader
	{
		bool IVLoadedAsset::IncreaseTextureRefCount(std::string _name)
		{
			if (s_Textures.find(_name) == s_Textures.end())
				return false;
			s_Textures[_name].TexData.RefCount++;
			return true;
		}
		bool IVLoadedAsset::DecreaseTextureRefCount(std::string _name)
		{
			if (s_Textures.find(_name) == s_Textures.end())
				return false;
			s_Textures[_name].TexData.RefCount--;

			if (s_Textures[_name].TexData.RefCount <= 0)
			{
				s_TotalRelaesedTexture++;
				stbi_image_free(s_Textures[_name].TexData.Data);
				s_Textures[_name].TexData.Valid = false;
			}

			return true;
		}
		bool IVLoadedAsset::IsTextueLoaded(std::string _name)
		{
			return s_Textures.find(_name) != s_Textures.end();
		}
		bool IVLoadedAsset::IsTextueLoaded(DataBlock::Image2D& _image)
		{
			bool _same_name = IsTextueLoaded(_image.Name);
			
			// if same name found
			if (_same_name)
			{
				// If it has the same seed
				if (s_Textures[_image.Name].TexData.Seed == _image.Seed)
					return true;
			}

			return false;
		}
		void IVLoadedAsset::FreeUnusedTexture()
		{
			for (auto iter = s_Textures.begin(); iter != s_Textures.end(); iter++)
			{
				if (iter->second.TexData.RefCount > 0 && iter->second.TexData.Valid)
				{
					s_TotalRelaesedTexture++;
					stbi_image_free(iter->second.TexData.Data);
					iter->second.TexData.Valid = false;
				}
			}
		}
		std::string IVLoadedAsset::RegisterTexture(std::string _name, Loader::TexturePkg _image_pkg)
		{
			_image_pkg.TexData.Name = _name;

			if (IsTextueLoaded(_image_pkg.TexData))
				return _image_pkg.TexData.Name;

			std::string _unique_name = CheckNameCollision(_name, CheckTextureNameExist);

			_image_pkg.TexData.Name = _unique_name;

			s_TotalRegistedTexture++;
			s_Textures.insert(std::make_pair(_unique_name, _image_pkg));

			return _unique_name;
		}
		DataBlock::Image2D* IVLoadedAsset::GetTextureData(std::string _name)
		{
			return &s_Textures[_name].TexData;
		}
		DataBlock::TextureType IVLoadedAsset::GetTextureType(std::string _name)
		{
			return s_Textures[_name].TexType;
		}

		bool IVLoadedAsset::CheckTextureNameExist(std::string _name)
		{
			return s_Textures.find(_name) != s_Textures.end();
		}

		std::string IVLoadedAsset::CreateTextureSeed(DataBlock::Image2D& _image)
		{
			std::string _seed;
			// Define the number of samples per diagonal
			const int numSamples = 10;

			// Calculate the step size for sampling along each diagonal
			float stepX = static_cast<float>(_image.Width) / numSamples;
			float stepY = static_cast<float>(_image.Height) / numSamples;

			// Sample pixels along the diagonal from top-left to bottom-right
			for (int i = 0; i < numSamples; ++i) {
				int x = static_cast<int>(i * stepX);
				int y = static_cast<int>(i * stepY);

				// Calculate the index of the pixel
				int index = (y * _image.Width + x) * _image.Channel;

				// Read pixel values at the calculated index
				unsigned char* p = _image.Data + index;

				for (int c = 0; c < _image.Channel; ++c) {
					_seed.append(std::to_string(static_cast<unsigned int>(p[c])));
				}

				// Process the sampled pixel values here
			}
			_seed.append("<-X->");
			// Sample pixels along the diagonal from top-right to bottom-left
			for (int i = 0; i < numSamples; ++i) {
				int x = static_cast<int>(_image.Width - 1 - (i * stepX));
				int y = static_cast<int>(i * stepY);

				// Calculate the index of the pixel
				int index = (y * _image.Width + x) * _image.Channel;

				// Read pixel values at the calculated index
				unsigned char* p = _image.Data + index;

				for (int c = 0; c < _image.Channel; ++c) {
					_seed.append(std::to_string(static_cast<unsigned int>(p[c])));
				}
			}

			_image.Seed = _seed;
			return _seed;
		}

		std::string IVLoadedAsset::CheckNameCollision(std::string _name, std::function<bool(std::string)> _cmp)
		{
			while (_cmp(_name))
			{
				// If the last char is not ) it means this isthe first instance
				if (_name.back() != ')')
					_name += "(1)";
				else
				{
					// If the code reach here it means the name is modefied with (index)
					// so we need to extract this index and increament it
					size_t last_open_index = _name.find_last_of('(');
					size_t last_close_index = _name.find_last_of(')');

					size_t index_digit_count = last_close_index - last_open_index;
					std::string digit = _name.substr(last_open_index + 1, index_digit_count);
					_name.replace(last_open_index + 1, index_digit_count - 1, std::to_string(std::stoi(digit) + 1));
				}
			}

			return _name;
		}

	}
}