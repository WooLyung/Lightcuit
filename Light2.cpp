#include "stdafx.h"
#include "Light2.h"

Light2::Light2(long x, long y, Dir dir)
	: Light(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light.png");
	uncoloredSpriteRenderer->SetTexture("Resources/Sprites/Gates/Light/light2_uncolored.png");

	input.push_back(Dir::LEFT);
	input.push_back(Dir::DOWN);

	SetRot(dir);
}

Light2::~Light2()
{
}