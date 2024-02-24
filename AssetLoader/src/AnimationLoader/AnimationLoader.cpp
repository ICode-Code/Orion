#include "AnimationLoader.h"


namespace OE1Core
{
	namespace Loader
	{
		Animation* AnimationLoader::LoadAnimation(std::string _path, DataBlock::BoneMap _bone_info_map)
		{

			Assimp::Importer _importer;
			const aiScene* _scene = _importer.ReadFile(_path, aiProcess_Triangulate);

			if (!_scene || !_scene->HasAnimations())
			{
				return nullptr;
			}
			Animation* animation_data = new Animation();

			ParseAnimation(_scene->mAnimations[0], animation_data, _bone_info_map, _scene);


			return animation_data;
		}


		void AnimationLoader::ParseAnimation(aiAnimation* _src, Animation* _dest, DataBlock::BoneMap& _bone_map, const aiScene* _scene)
		{
			_dest->m_Duration = (float)_src->mDuration;
			_dest->m_TickPerSecond = (float)_src->mTicksPerSecond;

			ParseNodeHeirarchy(_dest->m_RootNode, _scene->mRootNode);
			ReadBones(_src, _dest, _bone_map);
		}
		void AnimationLoader::ReadBones(const aiAnimation* _animation, Animation* _dest, DataBlock::BoneMap _bone)
		{
			unsigned int channel_count = _animation->mNumChannels;
			size_t boneCount = (size_t)_bone.size();

			for (unsigned int i = 0; i < channel_count; i++)
			{
				aiNodeAnim* _channel = _animation->mChannels[i];
				std::string _bone_name = _channel->mNodeName.data;

				if (_bone.find(_bone_name) == _bone.end())
				{
					_bone.insert(std::make_pair(_bone_name, DataBlock::BoneInfo()));
					_bone[_bone_name].ID = (int)boneCount;
					boneCount++;
				}
				KeyFrameChannel _keyframe_channel = ParseChannel(_channel);
				_dest->m_Bones.push_back(Bone(_bone_name, _bone[_bone_name].ID, _keyframe_channel));
			}
			_dest->m_BoneMap = _bone;
		}

		void AnimationLoader::ParseNodeHeirarchy(AnimNode& _node, const aiNode* _src)
		{
			_node.Name = _src->mName.data;
			_node.Transform = Utility::AI_TO_GLM::AiMatrix4x4ToGlm(&_src->mTransformation);
			_node.ChildCount = (size_t)_src->mNumChildren;

			for (size_t i = 0; i < _src->mNumChildren; i++)
			{
				AnimNode _new_node;
				ParseNodeHeirarchy(_new_node, _src->mChildren[i]);
				_node.Children.push_back(_new_node);
			}

		}
		KeyFrameChannel AnimationLoader::ParseChannel(aiNodeAnim* _channels)
		{
			KeyFrameChannel _data;

			// Position
			for (unsigned int i = 0; i < _channels->mNumPositionKeys; i++)
			{
				KeyPosition _pos;
				_pos.Position = Utility::AI_TO_GLM::VECTOR(_channels->mPositionKeys[i].mValue);
				_pos.TimeStamp = (float)_channels->mPositionKeys[i].mTime;
				_data.Positions.push_back(_pos);
			}

			// Rotation
			for (unsigned int i = 0; i < _channels->mNumRotationKeys; i++)
			{
				KeyRotation _rot;
				_rot.Rotation = Utility::AI_TO_GLM::AiQuatToGlm(_channels->mRotationKeys[i].mValue);
				_rot.TimeStamp = (float)_channels->mRotationKeys[i].mTime;
				_data.Rotations.push_back(_rot);
			}

			// Scale
			for (unsigned int i = 0; i < _channels->mNumScalingKeys; i++)
			{
				KeyScale _scale;
				_scale.Scale = Utility::AI_TO_GLM::VECTOR(_channels->mScalingKeys[i].mValue);
				_scale.TimeStamp = (float)_channels->mScalingKeys[i].mTime;
				_data.Scales.push_back(_scale);
			}

			return _data;
		}
	}
}