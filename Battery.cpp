#include "stdafx.h"
#include "Battery.h"

Battery::Battery(long x, long y)
	: Gate(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/battery.png");

	output.push_back(Dir::RIGHT);
}

Battery::~Battery()
{
}