#include "ShaderGenerator.h"


namespace OE1Core
{

	std::string ShaderGenerator::GetStandardVertexShader()
	{
		s_Source.clear();

		s_Source += R"(
#version 400 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Color;
layout (location = 2) in vec3 i_Normal;
layout (location = 3) in vec2 i_TexCoord;
layout (location = 4) in vec3 i_Tangent;
layout (location = 5) in vec3 i_Bitangent;
layout (location = 6) in mat4 i_InstanceMatrices;
layout (location = 10) in int i_RenderID;
layout (location = 11) in int i_MaterialID;


///////////////////////////////////////////////// STANDARD VERTEX SHADER OUTPUT //////////////////////////

out vec2		TexCoord;
out vec4		FragPosition;
out vec3		VertNormal;
out vec3        VertColor;
out vec3		Tangent;
out vec3		BiTangent;
flat out int	MaterialIndex;
flat out int	RenderID;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// SCENE TRANSFORM /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/scene_transform_uniform_block.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////



///// Entry

void main() 
{
	///////////////////////////////////////// VERETX -> FRAGMENT //////////////////////////

			MaterialIndex   = i_MaterialID;
			RenderID		= i_RenderID;
			TexCoord		= i_TexCoord;
			FragPosition	= i_InstanceMatrices * vec4(i_Position, 1.0f);
			Tangent			= i_Tangent;
			BiTangent		= i_Bitangent;
			VertNormal		= mat3(transpose(inverse(i_InstanceMatrices))) * i_Normal;  
			VertColor 		= i_Color;

	////////////////////////////////////////////////////////////////////////////////////////
	
			gl_Position = SceneCameraTransformBuffer[ActiveCameraIndex].PV * FragPosition;

}
        )";


		return std::exchange(s_Source, "");
	}
	std::string ShaderGenerator::GetStandardSkinnedMeshVertexShader()
	{
		s_Source.clear();

		s_Source += R"(
#version 400 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Color;
layout (location = 2) in vec3 i_Normal;
layout (location = 3) in vec2 i_TexCoord;
layout (location = 4) in vec3 i_Tangent;
layout (location = 5) in vec3 i_Bitangent;
layout (location = 6) in ivec4 i_BoneIndex;
layout (location = 7) in vec4  i_BoneWeight;
layout (location = 8) in mat4 i_InstanceMatrices;
layout (location = 12) in int i_RenderID;
layout (location = 13) in int i_MaterialID;
layout (location = 14) in int i_AnimationID;
layout (location = 15) in int i_BufferIdx;


///////////////////////////////////////////////// STANDARD VERTEX SHADER OUTPUT //////////////////////////

out vec2		TexCoord;
out vec4		FragPosition;
out vec3		VertNormal;
out vec3        VertColor;
out vec3		Tangent;
out vec3		BiTangent;
flat out int	MaterialIndex;
flat out int	RenderID;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// SCENE TRANSFORM /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/scene_transform_uniform_block.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// ANIMATION_BUFFER /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/animation_data_uniform_block.h>

/////////////////////////////////////////////////////////////////////////////////////////


///// Entry

void main() 
{
	

///////////////////////////////////////// SKALATON ANIMATION //////////////////////////

	mat4 FinalBoneTransformation =	Bones[i_BoneIndex[0]] * i_BoneWeight[0];
	FinalBoneTransformation +=		Bones[i_BoneIndex[1]] * i_BoneWeight[1];
	FinalBoneTransformation +=		Bones[i_BoneIndex[2]] * i_BoneWeight[2];
	FinalBoneTransformation +=		Bones[i_BoneIndex[3]] * i_BoneWeight[3];

////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// VERETX  FRAGMENT //////////////////////////

			MaterialIndex   = i_MaterialID;
			RenderID		= i_RenderID;
			TexCoord		= i_TexCoord;
			FragPosition	= i_InstanceMatrices * FinalBoneTransformation * vec4(i_Position.xyz, 1.0f);
			Tangent			= i_Tangent;
			BiTangent		= i_Bitangent;
			VertNormal		= mat3(transpose(inverse(i_InstanceMatrices * FinalBoneTransformation))) * i_Normal;
			VertNormal		= normalize(VertNormal);  
			VertColor 		= i_Color;

////////////////////////////////////////////////////////////////////////////////////////
	
			gl_Position = SceneCameraTransformBuffer[ActiveCameraIndex].PV * FragPosition;

}
        )";


		return std::exchange(s_Source, "");
	}
	std::string ShaderGenerator::GetStandardSkinnedMeshProxyVertexShader()
	{
		s_Source.clear();

		s_Source += R"(
#version 400 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Color;
layout (location = 2) in vec3 i_Normal;
layout (location = 3) in vec2 i_TexCoord;
layout (location = 4) in vec3 i_Tangent;
layout (location = 5) in vec3 i_Bitangent;
layout (location = 6) in ivec4 i_BoneIndex;
layout (location = 7) in vec4  i_BoneWeight;
layout (location = 8) in mat4 i_InstanceMatrices;
layout (location = 12) in int i_RenderID;
layout (location = 13) in int i_MaterialID;
layout (location = 14) in int i_AnimationID;
layout (location = 15) in int i_BufferIdx;


///////////////////////////////////////////////// STANDARD VERTEX SHADER OUTPUT //////////////////////////

out vec2		TexCoord;
out vec4		FragPosition;
out vec3		VertNormal;
out vec3        VertColor;
out vec3		Tangent;
out vec3		BiTangent;
flat out int	MaterialIndex;
flat out int	RenderID;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// SCENE TRANSFORM /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/scene_transform_uniform_block.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// ANIMATION_BUFFER /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/animation_data_uniform_block.h>

/////////////////////////////////////////////////////////////////////////////////////////


uniform mat4 Model;

///// Entry

void main() 
{
	

///////////////////////////////////////// SKALATON ANIMATION //////////////////////////

	mat4 FinalBoneTransformation =	Bones[i_BoneIndex[0]] * i_BoneWeight[0];
	FinalBoneTransformation +=		Bones[i_BoneIndex[1]] * i_BoneWeight[1];
	FinalBoneTransformation +=		Bones[i_BoneIndex[2]] * i_BoneWeight[2];
	FinalBoneTransformation +=		Bones[i_BoneIndex[3]] * i_BoneWeight[3];

////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////// VERETX  FRAGMENT //////////////////////////

			MaterialIndex   = i_MaterialID;
			RenderID		= i_RenderID;
			TexCoord		= i_TexCoord;
			FragPosition	= Model * FinalBoneTransformation * vec4(i_Position.xyz, 1.0f);
			Tangent			= i_Tangent;
			BiTangent		= i_Bitangent;
			VertNormal		= mat3(transpose(inverse(Model * FinalBoneTransformation))) * i_Normal;
			VertNormal		= normalize(VertNormal);  
			VertColor 		= i_Color;

////////////////////////////////////////////////////////////////////////////////////////
	
			gl_Position = SceneCameraTransformBuffer[ActiveCameraIndex].PV * FragPosition;

}
        )";


		return std::exchange(s_Source, "");
	}
	std::string ShaderGenerator::GetStandardProxyVertexShader()
	{
		s_Source.clear();

		s_Source += R"(
#version 400 core

layout (location = 0) in vec3 i_Position;
layout (location = 1) in vec3 i_Color;
layout (location = 2) in vec3 i_Normal;
layout (location = 3) in vec2 i_TexCoord;
layout (location = 4) in vec3 i_Tangent;
layout (location = 5) in vec3 i_Bitangent;
layout (location = 6) in mat4 i_InstanceMatrices;
layout (location = 10) in int i_RenderID;
layout (location = 11) in int i_MaterialID;


///////////////////////////////////////////////// STANDARD VERTEX SHADER OUTPUT //////////////////////////

out vec2		TexCoord;
out vec4		FragPosition;
out vec3		VertNormal;
out vec3        VertColor;
out vec3		Tangent;
out vec3		BiTangent;
flat out int	MaterialIndex;
flat out int	RenderID;

/////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////// SCENE TRANSFORM /////////////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/scene_transform_uniform_block.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////

uniform mat4 Model;

///// Entry

void main() 
{
	///////////////////////////////////////// VERETX -> FRAGMENT //////////////////////////

			MaterialIndex   = i_MaterialID;
			RenderID		= i_RenderID;
			TexCoord		= i_TexCoord;
			FragPosition	= Model * vec4(i_Position, 1.0f);
			Tangent			= i_Tangent;
			BiTangent		= i_Bitangent;
			VertNormal		= mat3(transpose(inverse(Model))) * i_Normal;  
			VertColor 		= i_Color;

	////////////////////////////////////////////////////////////////////////////////////////
	
			gl_Position = SceneCameraTransformBuffer[ActiveCameraIndex].PV * FragPosition;

}
        )";


		return std::exchange(s_Source, "");
	}
	std::string ShaderGenerator::GetDeferredPixelShader(AvailTexture& _texture_set)
	{
		return std::string("NOT_READY");
	}
	std::string ShaderGenerator::GetForwardPixelShader(AvailTexture& _texture_set)
	{
		s_Source.clear();

		CM_HeaderPixelShader();

		CM_Definations();

		FR_RegisterStandardVertexShaderInput();

		FR_RegisterUniforms();

		FR_RegisterCommonPixelShaderUtility();

		FR_RegisterPixelInfo();


		CM_OpenMainPixelShader();

		FR_ReadCommon();
		FR_IterateData(_texture_set);

		FR_ComputeFinalPixel();

		CM_CloseMainPixelShader();
		return std::exchange(s_Source, "");
	}
	void ShaderGenerator::CM_Definations()
	{
		s_Source.append("\n");
		s_Source.append("#define MAX_MATERIAL");
		s_Source.append(" ");
		s_Source.append(std::to_string(ORI_MAX_MATERIAL_PER_UNIFORM_BLOCK));
		s_Source.append("\n");
	}
	void ShaderGenerator::FR_RegisterUniforms()
	{
		s_Source += R"(
///////////////////////////////////////////////// UNIFORM BUFFER BLOCKS /////////////////////////////

#include <../ExternalAsset/Shaders/Header/UniformBlock/standard_static_mesh_texture_uniforms.h>
#include <../ExternalAsset/Shaders/Header/UniformBlock/material_data_uniform_block.h>

)";
	}
	void ShaderGenerator::CM_HeaderPixelShader()
	{
		s_Source += R"(
#version 400 core

layout(location = 0) out vec4 PixelColor;
layout(location = 1) out int UID;

layout(location = 2) out vec4 oPosition;
layout(location = 3) out vec4 oNormal;
layout(location = 4) out vec4 oMetalRougnessAOAlpha;
layout(location = 5) out vec4 oEmission;
)";
	}
	void ShaderGenerator::CM_OpenMainPixelShader()
	{
		s_Source += R"(

void main()
{

)";
	}
	void ShaderGenerator::CM_CloseMainPixelShader()
	{
		s_Source += R"(
}

)";
	}
	void ShaderGenerator::FR_RegisterStandardVertexShaderInput()
	{
		s_Source += R"(
///////////////////////////////////////////////// STANDARD VERTEX SHADER INPUT //////////////////////////
in vec2			TexCoord;
in vec4			FragPosition;
in vec3			VertNormal;
in vec3			VertColor;
in vec3			Tangent;
in vec3			BiTangent;
flat in int		MaterialIndex;
flat in int		RenderID;
        )";
	}
	void ShaderGenerator::FR_RegisterCommonPixelShaderUtility()
	{
		s_Source += R"(
///////////////////////////////////////////////// STANDARD NORMAL COMPUTATION FUNCTIONS //////////////////////////

vec3 ComputeNormal()
{
	vec3 tangentNormal = texture(t_NoneColorMapTexture, vec3(TexCoord,   TextureIndex[MaterialIndex].Normal)).xyz * 2.0 - 1.0;
	mat3 TBN = mat3(Tangent, BiTangent, normalize(VertNormal));
	return normalize(TBN * tangentNormal);
}
        )";
	}
	void ShaderGenerator::FR_RegisterPixelInfo()
	{
		s_Source += R"(

vec3 Color;
vec3 Normal;
vec3 Emission;
float AO;
float Metal = 0.0f;
float Alpha = 0.0f;
float Roughness = 0.0f;
float EmissionStength = 1.0f;
float Reflectivity = 0.04f;

        )";
	}
	void ShaderGenerator::FR_ReadCommon()
	{
		s_Source += R"(
EmissionStength = Materials[MaterialIndex].MetalRoughEmissionAlpha.b;
Alpha = Materials[MaterialIndex].MetalRoughEmissionAlpha.a;
Reflectivity = Materials[MaterialIndex].BaseReflectivityMetalFacRoughnessFac.r;

)";
	}
	void ShaderGenerator::FR_ReadAlbedoRaw()
	{
		s_Source += R"(
Color = Materials[MaterialIndex].Color.rgb;

)";
	}
	void ShaderGenerator::FR_ReadAlbedo()
	{
		s_Source += R"(

vec4 albedo_all = texture(t_ColorMapTexture, vec3(TexCoord,   TextureIndex[MaterialIndex].Color));
Color = albedo_all.rgb;
Alpha = albedo_all.a;

)";
	}
	void ShaderGenerator::FR_ReadNormal()
	{
		s_Source += R"(

Normal = ComputeNormal();

)";
	}
	void ShaderGenerator::FR_ReadNormalVertex()
	{
		s_Source += R"(

Normal = normalize(VertNormal);

)";
	}
	void ShaderGenerator::FR_ReadRoughness()
	{
		s_Source += R"(

Roughness = texture(t_NoneColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].Roughness)).r;

)";
	}
	void ShaderGenerator::FR_ReadRoughnessRaw()
	{
		s_Source += R"(

Roughness = Materials[MaterialIndex].MetalRoughEmissionAlpha.g;

)";
	}
	void ShaderGenerator::FR_ReadMetal()
	{
		s_Source += R"(

Metal = texture(t_NoneColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].Metal)).r;

)";
	}
	void ShaderGenerator::FR_ReadMetalRaw()
	{
		s_Source += R"(

Metal = Materials[MaterialIndex].MetalRoughEmissionAlpha.r;

)";
	}
	void ShaderGenerator::FR_ReadRoughMetal()
	{
		s_Source += R"(
vec4 mat_arg = texture(t_NoneColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].RoughnessMetal));
Metal = mat_arg.b;
Roughness = mat_arg.g;
)";
	}
	void ShaderGenerator::FR_ReadAO()
	{
		s_Source += R"(

AO = texture(t_NoneColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].AmbientOcclusion)).r;

)";
	}
	void ShaderGenerator::FR_ReadAORaw()
	{
		s_Source += R"(

AO = Materials[MaterialIndex].AmbientOcclusion.r;

)";
	}
	void ShaderGenerator::FR_ReadAlphaMask()
	{
		s_Source += R"(

Alpha = texture(t_NoneColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].AlphaMask)).a;

)";
	}
	void ShaderGenerator::FR_ReadEmission()
	{
		s_Source += R"(

Emission = texture(t_ColorMapTexture, vec3(TexCoord, TextureIndex[MaterialIndex].Emission)).rgb;

)";
	}
	void ShaderGenerator::FR_ReadEmissionRaw()
	{
		s_Source += R"(

Emission = Materials[MaterialIndex].EmissionColor.rgb;

)";
	}
	void ShaderGenerator::FR_ComputeFinalPixel()
	{
		s_Source += R"(
	float Depth = (gl_FragCoord.z / gl_FragCoord.w);
	PixelColor = vec4(Color, 1.0f);
	UID = RenderID;

	oPosition = FragPosition;
	oNormal = vec4(Normal, 1.0f);
	oMetalRougnessAOAlpha = vec4(Metal * Materials[MaterialIndex].BaseReflectivityMetalFacRoughnessFac.y, Roughness * Materials[MaterialIndex].BaseReflectivityMetalFacRoughnessFac.z, AO, Alpha);
	oEmission = vec4(Emission, Materials[MaterialIndex].MetalRoughEmissionAlpha.b);
	//oEmission.w = EmissionStength;

)";
	}

	void ShaderGenerator::FR_IterateData(AvailTexture& _texture_set)
	{

		_texture_set.HasDiffuse ? FR_ReadAlbedo() : FR_ReadAlbedoRaw();
		_texture_set.HasNormal ? FR_ReadNormal() : FR_ReadNormalVertex();

		if (_texture_set.HasRoughness_Metal)
			FR_ReadRoughMetal();
		else
		{
			_texture_set.HasRoughness ? FR_ReadRoughness() : FR_ReadRoughnessRaw();
			_texture_set.HasMetal ? FR_ReadMetal() : FR_ReadMetalRaw();
		}

		_texture_set.HasAo ? FR_ReadAO() : FR_ReadAORaw();
		_texture_set.HasEmission ? FR_ReadEmission() : FR_ReadEmissionRaw();
		
		if (_texture_set.HasAlphaMask)
			FR_ReadAlphaMask();
	}
}