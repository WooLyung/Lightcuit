#include "stdafx.h"
#include "Cursor.h"
#include "SpriteRenderer.h"
#include "Engine.h"

Cursor::Cursor()
{
}

Cursor::~Cursor()
{
}

void Cursor::OnStart()
{
	transform = GetComponent<Transform>();
	transform->SetIsRelative(false);
	transform->SetAnchor(256, 256);
	transform->SetScale(0.12f, 0.12f);

	spriteRenderer = AttachComponent<SpriteRenderer>();
	spriteRenderer->SetTexture("Resources/Sprites/UIs/Cursors/default_cursor.png");
	spriteRenderer->SetZ_index(100);
	spriteRenderer->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
}

void Cursor::OnUpdate()
{
	transform->SetPos(RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos()));
}

void Cursor::SetSpr(int code)
{
	if (code == 0)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Cursors/default_cursor.png");
	if (code == 1)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Cursors/move_cursor.png");
	if (code == 2)
		spriteRenderer->SetTexture("Resources/Sprites/UIs/Cursors/line_cursor.png");
}