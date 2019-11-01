#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class StageChoice :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

public:
	StageChoice();
	~StageChoice();

	void OnStart();
	void OnUpdate();
};