#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"

class Palette :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	// animations
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

public:
	Palette();
	~Palette();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};