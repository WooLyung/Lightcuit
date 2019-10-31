#include "stdafx.h"
#include "Light1.h"

Light1::Light1(long x, long y)
	: Light(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light1.png");

	input.push_back(Dir::LEFT);
}

Light1::~Light1()
{
}