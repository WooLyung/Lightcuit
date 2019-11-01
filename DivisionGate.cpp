#include "stdafx.h"
#include "DivisionGate.h"

DivisionGate::DivisionGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/divisionGate.png");
	uncoloredSpriteRenderer->SetTexture("Resources/Sprites/Gates/divisionGate_uncolored.png");

	input.push_back(Dir::LEFT);
	output.push_back(Dir::UP);
	output.push_back(Dir::DOWN);

	SetRot(dir);
}

DivisionGate::~DivisionGate()
{
}