#include "SkeletonAnimator.h"


namespace OE1Core
{
	SkeletonAnimator::SkeletonAnimator()
	{

	}
	SkeletonAnimator::~SkeletonAnimator()
	{

	}

	void SkeletonAnimator::UpdateAnimations(float _dt)
	{
		for (auto iter = s_AnimationSet.begin(); iter != s_AnimationSet.end(); iter++)
		{
			if(iter->second->m_OnTransition)
				iter->second->Interpolate(1.0f / iter->second->m_TickPerSecond);
			else
				iter->second->UpdateTransform(1.0f / iter->second->m_TickPerSecond);
		}
	}
	bool SkeletonAnimator::HasAnimation(uint32_t _id)
	{
		return s_AnimationSet.find(_id) != s_AnimationSet.end();
	}
	void SkeletonAnimator::RegisterAnimation(uint32_t _id, Animation* _animation)
	{
		if (s_AnimationSet.find(_id) != s_AnimationSet.end())
			return;

		s_AnimationSet.insert(std::make_pair(_id, _animation));
	}
	Animation* SkeletonAnimator::GetAnimation(uint32_t _id)
	{
		if (s_AnimationSet.find(_id) == s_AnimationSet.end())
			return nullptr;

		return s_AnimationSet[_id];
	}
	void SkeletonAnimator::PurgeAnimation(uint32_t _id)
	{
		if (s_AnimationSet.find(_id) == s_AnimationSet.end())
			return;

		s_AnimationSet.erase(_id);
	}
	int SkeletonAnimator::GetActiveAnimationCount()
	{
		return (int)s_AnimationSet.size();
	}
	

}