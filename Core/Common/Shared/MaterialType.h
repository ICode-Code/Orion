#ifndef OE1_MATERIAL_TYPE_H_
#define OE1_MATERIAL_TYPE_H_

namespace OE1Core
{
	enum class MaterialType : int
	{
		DEFAULT				= 0,
		DIFFUSE				= 1 << 0,
		NORMAL				= 1 << 1,
		METAL				= 1 << 2,
		ROUGHNESS			= 1 << 3,
		METAL_ROUGHNESS		= 1 << 4,
		ALPHA				= 1 << 5,
		EMISSIVE			= 1 << 6,
		AO					= 1 << 7
	};

	struct MaterialTextureAvailFlags
	{
		bool HasColor			= false;
		bool HasNormal			= false;
		bool HasMetal			= false;
		bool HasRoughness		= false;
		bool HasMetalRoughness	= false;
		bool HasAlpha			= false;
		bool HasEmission		= false;
		bool HasAO				= false;
	};

	struct MaterialTextureCount
	{
	public:
		int GetColorTextureCount() const { return NumberOfColorTexture; }
		int GetNonColorTextureCount() const { return NumberNonColorTexture; }

		void CountAvialTexture(MaterialTextureAvailFlags& _avial_texture)
		{
			if (_avial_texture.HasColor)
				NumberOfColorTexture++;
			if (_avial_texture.HasEmission)
				NumberOfColorTexture++;

			if (_avial_texture.HasNormal)
				NumberNonColorTexture++;
			if (_avial_texture.HasMetalRoughness)
			{
				NumberNonColorTexture++;
			}
			else
			{
				if (_avial_texture.HasMetal)
					NumberNonColorTexture++;
				if (_avial_texture.HasRoughness)
					NumberNonColorTexture++;
			}
			if (_avial_texture.HasAlpha)
				NumberNonColorTexture++;
			if (_avial_texture.HasAO)
				NumberNonColorTexture++;
		}
		// This call will increase texture count
		int GetNextColorIndex() { return NumberOfColorTexture++; }
		// This call will increase texture count
		int GetNextNonColorIndex() { return NumberNonColorTexture++; }

	private:
		int NumberOfColorTexture = 0;
		int NumberNonColorTexture = 0;
	};
}

#endif // !OE1_MATERIAL_TYPE_H_
