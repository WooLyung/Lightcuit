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

private:
	CommandList* changeColor;
	Color nowColor = { 1, 1, 1, 1 };
	Color toColor = { 1, 1, 1, 1 };
	Color8 color;

public:
	Line(long, long);
	~Line();

	void OnStart();
	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void SetColor(Color8);
	void SetColor(Color);
	Color8 GetColor() { return color; }

	Vec2L tilePos;
	Dir dir;

	Line* nextLine = nullptr;
	Line* preLine = nullptr;
	Gate* nextGate = nullptr;
	Gate* preGate = nullptr;
};