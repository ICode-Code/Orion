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


		/// ////////////////////////////////////// Block-structure ///////////////////////////////

		struct UniformBuffer
		{
			UniformBuffer(std::string name = "#") : Name(name) {};

			std::string			Name;
			unsigned int		Buffer = 0;
			unsigned int		BindingPoint = 0;
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
			LIGHT_UTILITY,
			ANIMATION_REGISTRY
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
