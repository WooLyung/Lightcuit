#include "stdafx.h"
#include "AddGate.h"

AddGate::AddGate(long x, long y, Dir dir)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/addGate.png");
	uncoloredSpriteRenderer->SetTexture("Resources/Sprites/Gates/addGate_uncolored.png");

	input.push_back(Dir::UP);
	input.push_back(Dir::DOWN);
	output.push_back(Dir::RIGHT);

	SetRot(dir);
}

AddGate::~AddGate()
{
}