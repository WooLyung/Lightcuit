#include "stdafx.h"
#include "Pen2.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

Pen2::Pen2()
{
}

Pen2::~Pen2()
{
}

void Pen2::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/pen2.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.1f, 0.1f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width, spriteRenderer->GetTexture()->GetSize().height)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * 0.5f - 2.3f,
			GetScene()->GetMainCamera()->GetCameraSize().height * -0.5f - 1.2f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * 0.5f - 2.3f,
			GetScene()->GetMainCamera()->GetCameraSize().height * -0.5f - 1.2f - pow(animTime - 1, 2) * 5);
		transform->SetRot(120 - (pow(animTime - 1, 2) + 1) * 120);

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

void Pen2::OnUpdate()
{
}

Transform* Pen2::GetTransform()
{
	return transform;
}

SpriteRenderer* Pen2::GetSpriteRenderer()
{
	return spriteRenderer;
}