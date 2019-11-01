#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Transform.h"

class StageClearObj :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

public:
	StageClearObj();
	~StageClearObj();

	void OnStart();
	void OnUpdate();
};