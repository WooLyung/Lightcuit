#include "stdafx.h"
#include "Gate.h"

Gate::Gate(long x, long y)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>();
	effect = AttachComponent<Effect>();
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);
}

Gate::~Gate()
{
}

Dir Gate::GetDir()
{
	return dir;
}

void Gate::SetDir(Dir dir)
{
	this->dir = dir;

	switch (dir)
	{
		case Dir::RIGHT:
			transform->SetRot(0);
			break;
		case Dir::DOWN:
			transform->SetRot(90);
			break;
		case Dir::LEFT:
			transform->SetRot(180);
			break;
		case Dir::UP:
			transform->SetRot(270);
			break;
	}
}

Transform* Gate::GetTransform()
{
	return transform;
}

void Gate::SetPos(int x, int y)
{
	transform->SetPos(x, y);
	tilePos = Vec2L(x, y);
}