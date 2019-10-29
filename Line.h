#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Transform.h"
#include "Gate.h"

class Gate;

class Line :
	public Object
{
private:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

public:
	Line(long, long);
	~Line();

	void OnStart();
	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	Vec2L tilePos;
	Dir dir;

	Line* nextLine = nullptr;
	Line* preLine = nullptr;
	Gate* nextGate = nullptr;
	Gate* preGate = nullptr;
};