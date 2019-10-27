#include "stdafx.h"
#include "Line.h"
#include "SpriteRenderer.h"

Line::Line(long x, long y)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Lines/line1.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	effect = AttachComponent<Effect>();
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);
}

Line::~Line()
{
}

void Line::OnStart()
{
}

Transform* Line::GetTransform()
{
	return transform;
}

SpriteRenderer* Line::GetSpriteRenderer()
{
	return spriteRenderer;
}