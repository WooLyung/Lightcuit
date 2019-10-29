#include "stdafx.h"
#include "SubGate.h"

SubGate::SubGate(long x, long y)
	: Gate(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/subGate.png");

	input.push_back(Dir::UP);
	input.push_back(Dir::DOWN);
	output.push_back(Dir::RIGHT);
}

SubGate::~SubGate()
{
}