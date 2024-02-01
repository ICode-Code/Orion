#ifndef OE1_BILLBOARD_INSTANCE_PKG_H_
#define OE1_BILLBOARD_INSTANCE_PKG_H_

#include <glm/glm.hpp>

namespace OE1Core
{
	/// <summary>
	/// This struct represet billboard in gpu, used for instance each billboard will have an 
	/// ID and transform
	/// which represent the world position
	/// </summary>
	struct ViewportBillboardInstancePkg {
		glm::mat4 Transform = glm::mat4(1.0f);
		uint32_t ID = -1;
	};
	constexpr size_t  ViewportBillboardInstancePkgSize = sizeof(ViewportBillboardInstancePkg);
}

#endif // !OE1_BILLBOARD_INSTANCE_PKG_H_
