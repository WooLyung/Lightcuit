#include "stdafx.h"
#include "Light2.h"

Light2::Light2(long x, long y)
	: Light(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light2.png");

	input.push_back(Dir::LEFT);
	input.push_back(Dir::DOWN);
}

Light2::~Light2()
{
}