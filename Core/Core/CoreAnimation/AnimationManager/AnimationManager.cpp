#include "AnimationManager.h"
#include "../GUI/MiniWindow/AnimationStateMachinePad.h"
#include "LogUI.h"

namespace OE1Core
{
	AnimationManager::AnimationManager()
	{
		s_AnimationBuffer = Memory::UniformBlockManager::GetBuffer(Memory::UniformBufferID::ANIMATION_REGISTRY);
		
		std::vector<glm::mat4> _placeholder;
		
		for (int i = 0; i < ORI_MAX_ANIMATION_PER_UNIFORM_BLOCK; i++)
			_placeholder.push_back(glm::mat4(1.0f));

		glBindBuffer(GL_UNIFORM_BUFFER, s_AnimationBuffer->Buffer);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, Memory::s_AnimationOffsetBufferSize * ORI_MAX_ANIMATION_PER_UNIFORM_BLOCK, _placeholder.data());
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

	}
	AnimationManager::~AnimationManager()
	{

	}
	void AnimationManager::AnimationSwitchCommandCreateHandler(std::string _name, uint32_t _entity_id)
	{
		CommandDef::AnimationSwitchCommandDef _command(ORI_COMMAND_DEF_ARGS(__FUNCTION__));

		_command.TargetAnimation = AssetManager::GetAnimation(_name);
		_command.EntityID = _entity_id;

		Command::PushAnimationSwitchCommand(_command);
	}
	void AnimationManager::HardSwitch(Animation* _animation, uint32_t _id)
	{
		SkeletonAnimator::s_AnimationSet[_id] = _animation;
	}
	void AnimationManager::UpdateAnimation(Animation* _animation, uint32_t _id)
	{
		
		if (!SkeletonAnimator::s_AnimationSet[_id]->HasValidAnimationSetCallback())
			SkeletonAnimator::s_AnimationSet[_id]->RegisterAnimationSetCallback(&AnimationManager::AnimationSwitchCommandCreateHandler);
		
		SkeletonAnimator::s_AnimationSet[_id]->SetNextAnimation(_animation, _id);
	}
	MemoryBufferLocator AnimationManager::RegisterAnimationInstance(Animation* _animation, uint32_t _entity_id)
	{

		MemoryBufferLocator _locator;

		_locator.BoneCount = _animation->GetBoneCount();
		_locator.BufferID = s_AnimationBuffer->Buffer;


		int active_animation_cout = SkeletonAnimator::GetActiveAnimationCount();
		_locator.BufferIndex = active_animation_cout;


		_locator.Offset = _locator.BoneCount * Memory::s_AnimationOffsetBufferSize;
		s_LastEndOffset = _locator.Offset;


	
		if (!SkeletonAnimator::HasAnimation(_entity_id))
			SkeletonAnimator::RegisterAnimation(_entity_id, _animation);

		return _locator;
	}
	bool AnimationManager::HasAnimation(uint32_t _id)
	{
		return SkeletonAnimator::HasAnimation(_id);
	}
	Animation* AnimationManager::GetAnimation(uint32_t _id)
	{
		Animation* _data = SkeletonAnimator::GetAnimation(_id);
		
		if (_data)
			return _data;
		else
			LOG_ERROR(LogLayer::Pipe("Animation Query returned NULL! now suppost to happen!", OELog::CRITICAL));

		return nullptr;
	}


	std::unordered_map<std::string, AnimationStateMachinePad*>& AnimationManager::GetStateMachineWins()
	{
		return s_StateMachineWindows;
	}
	bool AnimationManager::RegisterStateMachineWindow(std::string _name, AnimationStateMachinePad* _pad)
	{
		if (s_StateMachineWindows.find(_name) != s_StateMachineWindows.end())
			return false;

		s_StateMachineWindows.insert(std::make_pair(_name, _pad));
		return true;
	}
	bool AnimationManager::PurgeStateMachineWindow(std::string _name)
	{
		if (s_StateMachineWindows.find(_name) == s_StateMachineWindows.end())
			return false;

		delete s_StateMachineWindows[_name];
		s_StateMachineWindows.erase(_name);

		return true;
	}
}