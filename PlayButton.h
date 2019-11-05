#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "TextRenderer.h"

class PlayButton :
	public Object
{
private:
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	// animations
	bool isAnim = false;
	float animTime = 0;
	CommandList* appearAnim;

public:
	PlayButton(bool);
	~PlayButton();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};