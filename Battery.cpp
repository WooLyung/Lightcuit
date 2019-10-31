#include "stdafx.h"
#include "Battery.h"

Battery::Battery(long x, long y)
	: Gate(x, y)
{
	spriteRenderer->SetTexture("Resources/Sprites/Gates/battery.png");
	color = Color8(1, 0, 0);
	toColor = Color(1, 0, 0, 1);
	nowColor = Color(1, 0, 0, 1);
	effect->ClearEffectInfo()->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 0, 0, 1)));

	output.push_back(Dir::RIGHT);
}

Battery::~Battery()
{
}