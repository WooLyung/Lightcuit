#include "stdafx.h"
#include "AddGate.h"

AddGate::AddGate(long x, long y)
	: Gate(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/addGate.png");

	input.push_back(Dir::UP);
	input.push_back(Dir::DOWN);
	output.push_back(Dir::RIGHT);
}

AddGate::~AddGate()
{
}