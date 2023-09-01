#ifndef OE1_UNIFROM_MEMORY_BLOCK_H_
#define OE1_UNIFROM_MEMORY_BLOCK_H_


#include <glm/glm.hpp>
#include <string>


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



		/// ////////////////////////////////////// Block-structure ///////////////////////////////

		struct UniformBuffer
		{
			UniformBuffer(std::string name = "#") : Name(name) {};

			std::string			Name;
			unsigned int		Buffer = 0;
			unsigned int		BindingPoint = 0;
		};

		/// ///////////////////////////////////////////////////////////////////////////


		/// /////////////////////////////////////// Uniform Buffer Cata ///////////////////////
		enum class UniformBufferID
		{
			SCENE_TRANSFORM = 0,
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
