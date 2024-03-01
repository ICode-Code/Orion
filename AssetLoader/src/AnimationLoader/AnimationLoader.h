#ifndef OE1_ANIMATION_LOADER_H_
#define OE1_ANIMATION_LOADER_H_

#include "../Animation/Animation.h"
#include "../Util/LoaderUtil.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace OE1Core
{
	namespace Loader
	{
		class AnimationLoader
		{
		public:
			static std::vector<Animation*> LoadAnimation(std::string _path, DataBlock::BoneMap _bone_info_map);


		private:
			static void ReadBones(const aiAnimation* _animation, Animation* _dest, DataBlock::BoneMap _bones);
			static void ParseAnimation(aiAnimation* _src,  Animation* _dest, DataBlock::BoneMap& _bone_map, const aiScene* _scene);
			static void ParseNodeHeirarchy(AnimNode& _node, const aiNode* _src);
			static KeyFrameChannel ParseChannel(aiNodeAnim* _channels);
		};
	}
}

#endif // !OE1_ANIMATION_LOADER_H_
