#include "stdafx.h"
#include "ColorSet.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Effect.h"
#include "Engine.h"

ColorSet::ColorSet()
{
}

ColorSet::~ColorSet()
{
}

void ColorSet::OnStart()
{
	transform = GetComponent<Transform>();

	red = new Object;
	red->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/ColorSet/circle.png")
		->SetZ_index(100);
	red->GetComponent<Transform>()
		->SetAnchor(32, 32)
		->SetPos(-0.35f, 0.6f)
		->SetScale(0.7f, 0.7f);
	red->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 0, 0, 1)));

	green = new Object;
	green->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/ColorSet/circle.png")
		->SetZ_index(100);
	green->GetComponent<Transform>()
		->SetAnchor(32, 32)
		->SetPos(0, 0.6f)
		->SetScale(0.7f, 0.7f);
	green->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(0, 1, 0, 1)));

	blue = new Object;
	blue->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/ColorSet/circle.png")
		->SetZ_index(100);
	blue->GetComponent<Transform>()
		->SetAnchor(32, 32)
		->SetPos(0.35f, 0.6f)
		->SetScale(0.7f, 0.7f);
	blue->AttachComponent<Effect>()
		->PushEffectInfo(new ColorMatrixEffectInfo(Color(0, 0, 1, 1)));

	AttachChild(red);
	AttachChild(green);
	AttachChild(blue);

	SetIsEnable(false);
}

Color8 ColorSet::GetColor()
{
	Vec2F mouse = RG2R_InputM->GetMouseWorldPos();
	Vec2F mouse_red = mouse - red->GetComponent<Transform>()->GetWorldPos();
	Vec2F mouse_green = mouse - green->GetComponent<Transform>()->GetWorldPos();
	Vec2F mouse_blue = mouse - blue->GetComponent<Transform>()->GetWorldPos();

	if (mouse_red.Dot(mouse_red) <= 0.06f)
		return R;
	else if (mouse_green.Dot(mouse_green) <= 0.06f)
		return G;
	else if (mouse_blue.Dot(mouse_blue) <= 0.06f)
		return B;
	else
		return W;
}

void ColorSet::SetPos(float x, float y)
{
	transform->SetPos(x, y);
}