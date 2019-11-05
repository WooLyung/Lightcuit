#include "stdafx.h"
#include "Light1.h"

Light1::Light1(long x, long y, Dir dir)
	: Light(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light1.png");

	input.push_back(Dir::LEFT);

	SetRot(dir);
}

Light1::~Light1()
{
}