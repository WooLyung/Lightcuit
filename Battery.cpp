#include "stdafx.h"
#include "Battery.h"

Battery::Battery(long x, long y, Dir dir, Color8 color)
	: Gate(x, y, dir)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/battery.png");
	uncoloredSpriteRenderer->SetTexture("Resources/Sprites/Gates/battery_uncolored.png");
	this->color = color;
	toColor = Color(color.r, color.g, color.b, 1);
	nowColor = Color(color.r, color.g, color.b, 1);
	effect->ClearEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(toColor));

	output.push_back(Dir::RIGHT);

	SetRot(dir);
}

Battery::~Battery()
{
}