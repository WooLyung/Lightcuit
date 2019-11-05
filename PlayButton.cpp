#include "stdafx.h"
#include "PlayButton.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

PlayButton::PlayButton(bool isAnim)
{
	this->isAnim = isAnim;
}

PlayButton::~PlayButton()
{
}

void PlayButton::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Menus/playButton.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
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

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.9f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.9f);
		transform->SetRot(20 - (pow(animTime - 1, 2) + 1) * 50);

		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * -0.5f + 0.9f - pow(animTime - 1, 2) * 5,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * -0.5f + 0.9f);
		transform->SetRot(20 - (pow(animTime - 1, 2) + 1) * 50);
	}
}

void PlayButton::OnUpdate()
{
}

Transform* PlayButton::GetTransform()
{
	return transform;
}

SpriteRenderer* PlayButton::GetSpriteRenderer()
{
	return spriteRenderer;
}