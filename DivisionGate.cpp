#include "stdafx.h"
#include "DivisionGate.h"

DivisionGate::DivisionGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/divisionGate.png");

	input.push_back(Dir::LEFT);
	output.push_back(Dir::UP);
	output.push_back(Dir::DOWN);

	SetRot(dir);
}

DivisionGate::~DivisionGate()
{
}