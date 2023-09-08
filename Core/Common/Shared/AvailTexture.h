#ifndef OE1_AVAIL_TEXTURE_H_
#define OE1_AVAIL_TEXTURE_H_

#include "MaterialType.h"

namespace OE1Core
{
	class AvailTexture
	{
	public:
		AvailTexture() = default;
		~AvailTexture() = default;
		void Reset()
		{
			HasDiffuse = false;
			HasNormal = false;
			HasRoughness = false;
			HasMetal = false;
			HasRoughness_Metal = false;
			HasAlphaMask = false;
			HasEmission = false;
			HasAo = false;
		}

		MaterialType GetMaterialType()
		{
			MaterialType material_type = MaterialType::DEFAULT;

			if (HasDiffuse)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::DIFFUSE));
			if (HasNormal)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::NORMAL));
			if (HasRoughness_Metal)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::METAL_ROUGHNESS));
			else
			{
				if (HasMetal)
					material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::METAL));
				if (HasRoughness)
					material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::ROUGHNESS));
			}
			if (HasAlphaMask)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::ALPHA));
			if (HasEmission)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::EMISSIVE));
			if (HasAo)
				material_type = static_cast<MaterialType>(static_cast<int>(material_type) | static_cast<int>(MaterialType::AO));

			return material_type;
		}

		bool HasDiffuse = false;
		bool HasNormal = false;
		bool HasRoughness = false;
		bool HasMetal = false;
		bool HasRoughness_Metal = false;
		bool HasAlphaMask = false;
		bool HasEmission = false;
		bool HasAo = false;
	};
}

#endif // !OE1_AVAIL_TEXTURE_H_
