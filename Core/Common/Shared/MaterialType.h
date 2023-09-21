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
}

#endif // !OE1_MATERIAL_TYPE_H_
