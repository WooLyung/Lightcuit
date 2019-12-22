#include "stdafx.h"
#include "Palette.h"
#include "Engine.h"

Palette::Palette()
{
}

Palette::~Palette()
{
}

void Palette::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/MapEditor/palette.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.7f, 0.7f)
		->SetAnchor(0, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.2f);

		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			disappearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f - pow(animTime, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.2f);
		}, 0);
	disappearAnim->SetIsLoop(true);
}

void Palette::OnUpdate()
{

}

void Palette::Disappear()
{
	animTime = 0;
	disappearAnim->Start();
}

Transform* Palette::GetTransform()
{
	return transform;
}

SpriteRenderer* Palette::GetSpriteRenderer()
{
	return spriteRenderer;
}