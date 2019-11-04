#include "stdafx.h"
#include "Ruler1.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

Ruler1::Ruler1()
{
}

Ruler1::~Ruler1()
{
}

void Ruler1::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/WritingSupplies/ruler.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.17f, 0.17f)
		->SetAnchor(0, 0)
		->SetIsRelative(false)
		->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * -0.5f - 0.5f,
			GetScene()->GetMainCamera()->GetCameraSize().height * 0.5f + 1.3f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraSize().width * -0.5f - 0.5f,
			GetScene()->GetMainCamera()->GetCameraSize().height * 0.5f + 1.3f + pow(animTime - 1, 2) * 5);
		transform->SetRot(50 - (pow(animTime - 1, 2) + 1) * 50);

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

void Ruler1::OnUpdate()
{
}

Transform* Ruler1::GetTransform()
{
	return transform;
}

SpriteRenderer* Ruler1::GetSpriteRenderer()
{
	return spriteRenderer;
}