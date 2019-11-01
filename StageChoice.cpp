#include "stdafx.h"
#include "StageChoice.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "InGameScene.h"
#include "StageData.h"

StageChoice::StageChoice()
{
}

StageChoice::~StageChoice()
{
}

void StageChoice::OnStart()
{
	transform = GetComponent<Transform>()
		->SetAnchor(128, 128);
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/stageChoice.png");

	auto text = (new Object)->AttachComponent<TextRenderer>()
		->SetText("1스테이지")->SetTextColor(Color(0, 0, 0))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)->GetOwner();
	text->ChangeParent(this);
	text->GetComponent<TextRenderer>()->SetZ_index(1);
}

void StageChoice::OnUpdate()
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		Vec2F vec = RG2R_InputM->GetMouseWorldPos() - transform->GetPos();

		if (vec.Dot(vec) <= 1)
		{
			StageData::GetInstance()->stage = 1;
			RG2R_SceneM->ChangeScene(new InGameScene, true);
		}
	}
}