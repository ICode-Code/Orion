#ifndef OE1_UNIFROM_MEMORY_BLOCK_H_
#define OE1_UNIFROM_MEMORY_BLOCK_H_


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

		struct __declspec(dllexport) SceneTransfrom
		{
			glm::mat4 Projection;
			glm::mat4 View;
			glm::mat4 PV;
			glm::vec3 CameraPosition;
			float Delta;
		};
		inline static constexpr size_t s_SceneTransformBufferSize = sizeof(SceneTransfrom);

		/// ///////////////////////////////////////////////////////////////////



		/// //////////////////////////////////// Infinte Grid Param /////////////
		struct __declspec(dllexport) InfiniteGrid
		{
			glm::vec4 ColorLight;
			glm::vec4 ColorBold;
			float Scale;
		};
		inline static constexpr size_t s_InfiniteGridBufferSize = sizeof(InfiniteGrid);

		/// //////////////////////////////////////////////////////////////////////////


		/// ////////////////////////////////////// Block-structure ///////////////////////////////

		struct __declspec(dllexport) UniformBuffer
		{
			UniformBuffer(std::string name = "#") : Name(name) {};

			std::string			Name;
			unsigned int		Buffer = 0;
			unsigned int		BindingPoint = 0;
		};

		/// ///////////////////////////////////////////////////////////////////////////


		/// /////////////////////////////////////// Uniform Buffer Cata ///////////////////////
		enum class __declspec(dllexport) UniformBufferID
		{
			SCENE_TRANSFORM = 0,
			INFIN_GRID,
			MATERIAL_PROPERTY,
			TEXTURE_ACCESS_INDEX,
			ENVIRONMENT_VARIABLES,
			POINT_LIGHT,
			DIRECTIONAL_LIGHT,
			LIGHT_UTILITY
		};

		/// ///////////////////////////////////////////////////////////////////////////

	}
}

#endif // !OE1_UNIFROM_MEMORY_BLOCK_H_
