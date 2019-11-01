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
	SpriteRenderer* uncoloredSpriteRenderer;
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

	Color8 color;
	Color nowColor = { 1, 1, 1, 0 };
	Color toColor = { 1, 1, 1, 0 };

	Dir dir = Dir::RIGHT;

public:
	Gate(long, long, Dir);
	~Gate();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();
	SpriteRenderer* GetUncoloredRenderer();
	Vec2L tilePos;
	Dir GetDir();
	Color8 GetColor() { return color; }

	void SetDir(Dir);
	void SetPos(int, int);
	void SetRot(Dir);

	void SetColor(Color8);
	void SetColor(Color);

	std::vector<Line*> nextLine;
	std::vector<Line*> preLine;

	std::vector<Dir> input;
	std::vector<Dir> output;

	virtual std::type_index GetID(void) = 0;
};