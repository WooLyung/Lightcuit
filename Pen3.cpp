#include "stdafx.h"
#include "Pen3.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

Pen3::Pen3()
{
}

Pen3::~Pen3()
{
}

void Pen3::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/pen3.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.08f, 0.08f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * 0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraSize().height * -0.5f - 0.7f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * 0.5f - 0.4f,
			GetScene()->GetMainCamera()->GetCameraSize().height * -0.5f - 0.7f - pow(animTime - 1, 2) * 5);
		transform->SetRot(-120 - (pow(animTime - 1, 2) + 1) * -120);

		if (animTime >= 1)
		{
			animTime = 0;
			appearAnim->Stop();
			state = WritingSuppliesState::wait;
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();
}

void Pen3::OnUpdate()
{
}

Transform* Pen3::GetTransform()
{
	return transform;
}

SpriteRenderer* Pen3::GetSpriteRenderer()
{
	return spriteRenderer;
}