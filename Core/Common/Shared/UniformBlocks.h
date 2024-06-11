#ifndef OE1_UNIFROM_MEMORY_BLOCK_H_
#define OE1_UNIFROM_MEMORY_BLOCK_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>


// Suppress warning C4251 when including GLM headers.
// Explanation: GLM is a header-only library and does not need a DLL interface.
// The warning is suppressed because it doesn't apply to GLM and can be safely ignored.
#pragma warning(disable: 4251)

namespace OE1Core
{
	namespace Memory
	{

		/// //////////////////////////// SceneTransfrom-Block //////////////////////

		struct SceneTransfrom
		{
			glm::mat4 Projection;
			glm::mat4 View;
			glm::mat4 PV;
			glm::vec3 CameraPosition;
			float Delta;
		};
		inline static constexpr size_t s_SceneTransformBufferSize = sizeof(SceneTransfrom);

		/// ///////////////////////////////////////////////////////////////////

		/// ////////////////////////////////////// EnvironmentVariables-Block ///////////////////////////////
		struct EnvironmentVariablesBuffer
		{
			float WorldLightIntensity = 1.0f;  // 4 bytes, offset 0
			float Exposure = 1.0f;             // 4 bytes, offset 4
			float Gamma = 2.2f;                // 4 bytes, offset 8
			float Fresnel = 1.0f;              // 4 bytes, offset 12

			glm::vec4 SunColor = glm::vec4(1.0f);         // 16 bytes, offset 16
			glm::vec4 SunDirection = glm::vec4(1.0f);     // 16 bytes, offset 32

			float SunBrightness = 1.0f;        // 4 bytes, offset 48
			float SunRadius = 1.0f;            // 4 bytes, offset 52
			float BloomInfluence = 0.22f;    // 4 byte, 
			float BloomFilterRadius = 0.6f; // 4 byte

			glm::vec4 FogColor = glm::vec4(0.5f);         // 16 bytes, offset 64

			float FogGradiant = 4.73016f;          // 4 bytes, offset 80
			float FogDensity = 0.00317f;           // 4 bytes, offset 84
			float FogIntensity = 0.5f;         // 4 bytes, offset 88
			float FogLowerLimit = -0.2f;        // 4 bytes, offset 92
			float FogUpperLimit = 0.2f;        // 4 bytes, offset 96
			int UseFog = false;                 // 4 bytes, offset 100

			float Brightness = 0.1f;
			float Contrast = 1.2f;
			float Saturation = 1.3f;
			float Hue = 0.0f;
		};


		inline static constexpr size_t s_EnvironmentVariablesBufferSize = sizeof(EnvironmentVariablesBuffer);
		/// /////////////////////////////////////////////////////////////////////////////////////

		/// //////////////////////////// Animation-Offsets //////////////////////

		struct AnimationOffset
		{
			glm::mat4 Offsets;
		};
		inline static constexpr size_t s_AnimationOffsetBufferSize = sizeof(AnimationOffset);

		/// ///////////////////////////////////////////////////////////////////



		/// //////////////////////////////////// Infinte Grid Param /////////////
		struct InfiniteGrid
		{
			glm::vec4 ColorLight;
			glm::vec4 ColorBold;
			float Scale;
		};
		inline static constexpr size_t s_InfiniteGridBufferSize = sizeof(InfiniteGrid);

		/// //////////////////////////////////////////////////////////////////////////


		/// //////////////////////////////////// Core Light Pkg /////////////
		struct CoreLight
		{
			glm::vec4 Position		= glm::vec4(0.0f, 5.0f, 0.0f, 1.0f);
			glm::vec4 Direction		= glm::vec4(-0.2f, -1.0f, -0.3f, 1.0f);
			glm::vec4 Color			= glm::vec4(1.0f);
			// for Dir light
			// Args[0] ShadowMap Index, Args[1] BufferDataIndex, Args[2] CascadeCount, Args[3] Shadow Resolution
			//
			// For PointLight
			// Args[0] ShadowMap Index, 
			glm::ivec4 Args				= glm::ivec4(-1);
			
			float Radius				= 1.0f;
			float InnerCutoff			= glm::cos(glm::radians(12.5f));
			float OuterCutoff			= glm::cos(glm::radians(7.5f));
			float padd;

			float Intensity			= 5.0f;
			float ShadowBias		= 0.001f;
			float TempratureFactor	= 0.5f;
			int  AffectWorld		= true;
			int  Static				= false;
			int  CastShadow			= false;
			int  SoftShadow			= false;
			int  UseTemprature		= false;
		};
		inline static constexpr size_t s_CoreLightPackageBufferSize = sizeof(CoreLight);

		/// //////////////////////////////////////////////////////////////////////////


		/// //////////////////////////////////// Light Util Param /////////////
		struct LightUtil
		{
			int PointLightCount = 0;
			int ActivePointLightCount = 0;

			int DirectionalLightCount = 0;
			int ActiveDirectionalLightCount = 0;

			int SpotLightCount = 0;
			int ActiveSpotLight = 0;
		};
		inline static constexpr size_t s_LightUtilPackageBufferSize = sizeof(LightUtil);

		/// //////////////////////////////////////////////////////////////////////////

		/// ////////////////////////////////////// Block-structure ///////////////////////////////

		struct UniformBuffer
		{
			UniformBuffer(std::string name = "##") : Name(name) {};
			size_t				Capacity = 0;
			size_t				UsedCapacity = 0;
			std::string			Name;
			unsigned int		Buffer = 0;
			unsigned int		BindingPoint = 0;

			/// <summary>
			/// Add the used capacity out side and send the value
			/// </summary>
			/// <param name="_capacity">Used Capacity</param>
			void SetUsedCapacity(size_t _capacity)
			{
				UsedCapacity = _capacity;
			}
			void SetMaxCapacity(size_t _capacity) { Capacity = _capacity; }

			void Update(size_t _size, int _offset, void* _data)
			{
				glBindBuffer(GL_UNIFORM_BUFFER, Buffer);
				glBufferSubData(GL_UNIFORM_BUFFER, _offset, _size, _data);
				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}
		};

		/// ///////////////////////////////////////////////////////////////////////////


		/// /////////////////////////////////////// Uniform Buffer Cata ///////////////////////
		enum class UniformBufferID
		{
			SCENE_TRANSFORM = 0,
			INFIN_GRID,
			MATERIAL_REGISTRY,
			TAI_REGISTRY,
			ENVIRONMENT_VARIABLES,
			POINT_LIGHT_REGISTRY,
			DIRECTIONAL_LIGHT_REGISTRY,
			SPOT_LIGHT_REGISTRY,
			LIGHT_UTILITY,
			ANIMATION_REGISTRY
		};

		enum class UniformBufferIDArray
		{
			ANIMATION_REGISTRY_ARRAY = 0
		};

		/// ///////////////////////////////////////////////////////////////////////////



		/// /////////////////////////////////// MaterialProperties-Block //////////////////////

		/*
		* Using glm::vec4 ensure that each member of
		* the struct occupies a contiguous 16-byte block,
		* which is the default alignment for uniform buffers
		*/
		struct MaterialProperties
		{
			glm::vec4 Color = glm::vec4(1.0f);
			glm::vec4 EmissionColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			glm::vec4 AmbientOcclusion = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
			glm::vec4 MetalRoughEmissionAlpha = glm::vec4(0.0f, 0.5f, 0.0f, 1.0f); // m_Metal, m_Roughness, m_EmissionStength, m_Alpha
			glm::vec4 BaseReflectivity_RF_MF = glm::vec4(0.02f, 1.0f, 1.0f, 1.0f); // m_BaseReflectivity, Roughness Factor, Metalic Factor, padding
		};
		inline static constexpr size_t s_MaterialPropertiesBufferSize = sizeof(MaterialProperties);


		struct TextureAccessIndex
		{
			/// Color Texture
			int Color				= -1;
			int Emission			= -1;

			/// Non-Color Texture
			int Normal				= -1;
			int Roughness			= -1;
			int Metal				= -1;
			int RoughnessMetal		= -1;
			int AmbientOcclusion	= -1;
			int AlphaMask			= -1;
		};
		inline static constexpr size_t s_TextureAccessIndexBufferSize = sizeof(TextureAccessIndex);

		/// /////////////////////////////////////////////////////////////////////////

	}
}

#endif // !OE1_UNIFROM_MEMORY_BLOCK_H_
