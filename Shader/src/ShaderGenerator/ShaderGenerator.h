#ifndef OE1_SHADER_GENERATOR_H_
#define OE1_SHADER_GENERATOR_H_

#include <string>
#include <utility>
#include "AvailTexture.h"
#include "PreDef.h"


// Suppress warning C4251: std::string
#pragma warning(disable: 4251)

namespace OE1Core
{
	class __declspec(dllexport) ShaderGenerator
	{
	public:
		ShaderGenerator() = default;
		~ShaderGenerator() = default;
		static std::string GetStandardVertexShader();
		static std::string GetStandardSkinnedMeshVertexShader();
		static std::string GetStandardSkinnedMeshProxyVertexShader();
		static std::string GetStandardProxyVertexShader();
		static std::string GetForwardPixelShader(AvailTexture& _texture_set);
		static std::string GetDeferredPixelShader(AvailTexture& _texture_set);
		

	private: // data
		inline static std::string s_Source;

	private: // Common
		static void CM_HeaderPixelShader();
		static void CM_Definations();
		static void CM_OpenMainPixelShader();
		static void CM_CloseMainPixelShader();

	private: // forward
		static void FR_RegisterStandardVertexShaderInput();
		static void FR_RegisterUniforms();
		static void FR_RegisterCommonPixelShaderUtility();
		static void FR_RegisterPixelInfo();
		static void FR_IterateData(AvailTexture& _texture_set);
		static void FR_ComputeFinalPixel();

	private: // forward read
		static void FR_ReadAlbedo();
		static void FR_ReadAlbedoRaw();
		static void FR_ReadNormal();
		static void FR_ReadNormalVertex();
		static void FR_ReadRoughness();
		static void FR_ReadRoughnessRaw();
		static void FR_ReadMetal();
		static void FR_ReadMetalRaw();
		static void FR_ReadRoughMetal();
		static void FR_ReadAO();
		static void FR_ReadAORaw();
		static void FR_ReadAlphaMask();
		static void FR_ReadEmission();
		static void FR_ReadEmissionRaw();
		static void FR_ReadCommon();

	};
}

#endif // !OE1_SHADER_GENERATOR_H_
