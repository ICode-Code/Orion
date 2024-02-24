#ifndef OE1_ANIM_NODE_H_
#define OE1_ANIM_NODE_H_

#include "../Util/DataBlock.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <string>
#include <vector>
#include <map>
namespace OE1Core
{
	struct AnimNode 
	{
		glm::mat4 Transform;
		std::string Name;
		std::vector<AnimNode> Children;
		size_t ChildCount;
	};

	struct KeyPosition
	{
		glm::vec3 Position;
		float TimeStamp;
	};
	struct KeyRotation
	{
		glm::quat Rotation;
		float TimeStamp;
	};

	struct KeyScale
	{
		glm::vec3 Scale;
		float TimeStamp;
	};

	struct KeyFrameChannel
	{
		std::vector<KeyPosition> Positions;
		std::vector<KeyRotation> Rotations;
		std::vector<KeyScale> Scales;
	};
}

#endif // !OE1_ANIM_NODE_H_
