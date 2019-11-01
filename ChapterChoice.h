#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class ChapterChoice :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

public:
	ChapterChoice();
	~ChapterChoice();

	void OnStart();
	void OnUpdate();
};