#include "stdafx.h"
#include "SubGate.h"

SubGate::SubGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/subGate.png");

	input.push_back(Dir::LEFT);
	input.push_back(Dir::DOWN);
	output.push_back(Dir::RIGHT);

	SetRot(dir);
}

SubGate::~SubGate()
{
}