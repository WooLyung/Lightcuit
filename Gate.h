#pragma once
#include "Object.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Transform.h"
#include "Line.h"
#include "CommandList.h"

class Line;

class Gate :
	public Object
{
private:
	CommandList* changeColor;

protected:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;
	Color8 color;
	Color nowColor = { 0.2f, 0.2f, 0.2f, 1 };
	Color toColor = { 0.2f, 0.2f, 0.2f, 1 };

	Dir dir = Dir::RIGHT;

public:
	Gate(long, long);
	~Gate();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	Vec2L tilePos;
	Dir GetDir();
	Color8 GetColor() { return color; }

	void SetDir(Dir);
	void SetPos(int, int);
	void SetColor(Color8);
	void SetColor(Color);

	std::vector<Line*> nextLine;
	std::vector<Line*> preLine;

	std::vector<Dir> input;
	std::vector<Dir> output;

	virtual std::type_index GetID(void) = 0;
};