#include "stdafx.h"
#include "AnimationRenderData.h"
#include "Engine.h"

AnimationRenderData::AnimationRenderData()
{
}

AnimationRenderData::~AnimationRenderData()
{
}

Rect AnimationRenderData::GetVisibleArea()
{
	return visibleArea;
}


AnimationRenderData* AnimationRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}

AnimationRenderData* AnimationRenderData::SetVisibleArea(float a, float b, float c, float d)
{
	visibleArea = Rect(a, b, c, d);

	return this;
}

AnimationRenderData* AnimationRenderData::SetVisibleArea()
{
	visibleArea = Rect(0, 0, animations[0].GetTexture(0)->GetSize().width, animations[0].GetTexture(0)->GetSize().height);

	return this;
}

std::vector<Textures>* AnimationRenderData::GetAnimations()
{
	return &animations;
}

int AnimationRenderData::GetTargetAnim()
{
	return targetAnim;
}

int AnimationRenderData::GetNowIndex()
{
	return nowIndex;
}

float AnimationRenderData::GetInterval()
{
	return interval;
}

float AnimationRenderData::GetTime()
{
	return time;
}

bool AnimationRenderData::GetIsLoop()
{
	return isLoop;
}

AnimationRenderData* AnimationRenderData::SetTargetAnim(int targetAnim)
{
	this->targetAnim = targetAnim;

	return this;
}

AnimationRenderData* AnimationRenderData::SetNowIndex(int nowIndex)
{
	this->nowIndex = nowIndex;

	return this;
}

AnimationRenderData* AnimationRenderData::SetInterval(float interval)
{
	this->interval = interval;

	return this;
}

AnimationRenderData* AnimationRenderData::SetTime(float time)
{
	this->time = time;

	return this;
}

AnimationRenderData* AnimationRenderData::SetIsLoop(bool isLoop)
{
	this->isLoop = isLoop;

	return this;
}