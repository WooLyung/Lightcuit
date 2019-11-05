#include "stdafx.h"
#include "ReverseGate.h"

ReverseGate::ReverseGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/reverseGate.png");

	input.push_back(Dir::LEFT);
	output.push_back(Dir::RIGHT);

	SetRot(dir);
}

ReverseGate::~ReverseGate()
{
}