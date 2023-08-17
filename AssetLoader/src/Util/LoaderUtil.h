#ifndef OE1_LOADER_UTIL_H_
#define OE1_LOADER_UTIL_H_

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <assimp/scene.h>

namespace OE1Core
{
	namespace Utility
	{
		namespace AI_TO_GLM
		{
			glm::vec3 VECTOR(aiVector3D _From);
			glm::vec2 VECTOR(aiVector2D _From);
			glm::mat4 AiMatrix4x4ToGlm(const aiMatrix4x4* from);
		}
	}
}

#endif // !OE1_LOADER_UTIL_H_
