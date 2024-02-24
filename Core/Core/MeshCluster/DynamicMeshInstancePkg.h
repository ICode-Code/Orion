#ifndef OE1_DYNAMIC_MESH_INSTANCE_PKG_H_
#define OE1_DYNAMIC_MESH_INSTANCE_PKG_H_

#include <glm/glm.hpp>

namespace OE1Core
{
	/// <summary>
	/// This Data is constructed and sent to GPU
	/// per instance,
	/// If you modify this struct even change the order you need to reconfigure the VAO 
	/// construction in AssetFactory.cpp inside --GLInitlization-- function
	/// If you add another paramater for instance you need to do the same
	/// </summary>
	struct DynamicMeshInstancePkg
	{
		/// <summary>
		/// Define Instance World TransformComponent
		/// </summary>
		glm::mat4 TransformComponent = glm::mat4(1.0f);

		/// <summary>
		/// Instance ID 
		/// We generate and send it to GPU we could use the gl_InstanceID but
		/// when we implement frustum culling the Instance ID on CPU side and GPU side do not match
		/// which cause issue 
		/// </summary>
		int RenderID = -1;
		int MaterialID = -1;
		int AnimationID = -1;

	};

	inline static constexpr size_t DynamicMeshInstancePkgSize = sizeof(DynamicMeshInstancePkg);
}

#endif // !OE1_DYNAMIC_MESH_INSTANCE_PKG_H_
