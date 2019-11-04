#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"

class Ruler2 :
	public Object
{
private:
	enum WritingSuppliesState {
		appear, wait, disappear
	};

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	WritingSuppliesState state = appear;

	// animations
	float animTime = 0;
	CommandList* appearAnim;

public:
	Ruler2();
	~Ruler2();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};