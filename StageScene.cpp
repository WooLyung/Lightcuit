#include "stdafx.h"
#include "StageScene.h"
#include "TextRenderer.h"
#include "StageChoice.h"
#include "Transform.h"

StageScene::StageScene()
{
}

StageScene::~StageScene()
{
}

void StageScene::OnStart()
{
	CreateObject()->AttachComponent<TextRenderer>()
		->SetText("스테이지 선택")->SetTextColor(Color(1, 1, 1))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);

	AttachObject(new StageChoice)
		->GetComponent<Transform>()
		->SetPos(3, 1.5f);
}