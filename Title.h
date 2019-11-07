#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class Title
	: public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	CommandList* appearAnim;
	CommandList* disappearAnim;
	float animTime = 0;

public:
	Title();
	~Title();

	void NextScene();
};

