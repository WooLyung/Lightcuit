#include "stdafx.h"
#include "Popup.h"
#include "Engine.h"

Popup::Popup()
{
}

Popup::~Popup()
{
}

void Popup::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/PopUps/stageFail.png");
	transform = GetComponent<Transform>()
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, 0)
		->SetIsRelative(false)
		->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f)
		->SetScale(0.08f, 0.08f);
}