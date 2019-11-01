#include "stdafx.h"
#include "ChapterChoice.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

ChapterChoice::ChapterChoice()
{
}

ChapterChoice::~ChapterChoice()
{
}

void ChapterChoice::OnStart()
{
	transform = GetComponent<Transform>()
		->SetAnchor(128, 128);
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/chapterChoice.png");

	auto text = (new Object)->AttachComponent<TextRenderer>()
		->SetText("1ц╘ем")->SetTextColor(Color(0, 0, 0))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)->GetOwner();
	text->ChangeParent(this);
	text->GetComponent<TextRenderer>()->SetZ_index(1);
}

void ChapterChoice::OnUpdate()
{
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		Vec2F vec = RG2R_InputM->GetMouseWorldPos() - transform->GetPos();

		if (vec.Dot(vec) <= 1)
		{
			StageData::GetInstance()->chapter = 1;
			RG2R_SceneM->ChangeScene(new StageScene, true);
		}
	}
}