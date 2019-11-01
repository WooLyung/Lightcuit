#include "stdafx.h"
#include "ChapterScene.h"
#include "TextRenderer.h"
#include "ChapterChoice.h"
#include "Transform.h"

ChapterScene::ChapterScene()
{
}

ChapterScene::~ChapterScene()
{
}

void ChapterScene::OnStart()
{
	CreateObject()->AttachComponent<TextRenderer>()
		->SetText("Ã©ÅÍ ¼±ÅÃ")->SetTextColor(Color(1, 1, 1))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);

	AttachObject(new ChapterChoice)
		->GetComponent<Transform>()
		->SetPos(3, 1.5f);
}