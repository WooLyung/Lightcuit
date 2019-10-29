#include "stdafx.h"
#include "ReverseGate.h"

ReverseGate::ReverseGate(long x, long y)
	: Gate(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/reverseGate.png");

	input.push_back(Dir::LEFT);
	output.push_back(Dir::RIGHT);
}

ReverseGate::~ReverseGate()
{
}