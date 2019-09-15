#pragma once
#include "Math.h"
#include "Texture.h"
#include "Textures.h"
#include <vector>

class AnimationRenderData
{
private:
	std::vector<Textures> animations;
	Rect visibleArea = { 0, 0, 0, 0 };
	int targetAnim = 0;
	int nowIndex = 0;
	float interval = 1;
	bool isLoop = true;

public:
	AnimationRenderData();
	~AnimationRenderData();

	std::vector<Textures>* GetAnimations();
	Rect GetVisibleArea();
	int GetTargetAnim();
	int GetNowIndex();
	float GetInterval();
	bool GetIsLoop();

	AnimationRenderData* SetVisibleArea(Rect);
	AnimationRenderData* SetVisibleArea();
	AnimationRenderData* SetTargetAnim(int);
	AnimationRenderData* SetNowIndex(int);
	AnimationRenderData* SetInterval(float);
	AnimationRenderData* SetIsLoop(bool);
};