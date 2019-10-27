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
protected:
	SpriteRenderer* spriteRenderer;
	Effect* effect;
	Transform* transform;

	Dir dir = Dir::RIGHT;

public:
	Gate(long, long);
	~Gate();

	Transform* GetTransform();
	Vec2L tilePos;
	Dir GetDir();

	void SetDir(Dir);
	void SetPos(int, int);

	std::list<Line*> connectedLine;
	std::vector<Line*> nextLine;
	std::vector<Line*> preLine;

	std::vector<Dir> input;
	std::vector<Dir> output;
};