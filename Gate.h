#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Transform.h"
#include "Line.h"

class Line;

class Gate :
	public Object
{
private:
	CommandList* changeColor;
	Color nowColor = { 1, 1, 1, 1 };
	Color toColor = { 1, 1, 1, 1 };
	Color8 color = W;

protected:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

	Dir dir = Dir::RIGHT;

public:
	Gate(long, long);
	~Gate();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	Vec2L tilePos;
	Dir GetDir();

	void SetDir(Dir);
	void SetPos(int, int);
	void SetColor(Color8);

	std::vector<Line*> nextLine;
	std::vector<Line*> preLine;

	std::vector<Dir> input;
	std::vector<Dir> output;

	virtual std::type_index GetID(void) = 0;
};