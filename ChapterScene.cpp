#include "stdafx.h"
#include "ChapterScene.h"
#include "TextRenderer.h"
#include "ChapterChoice.h"
#include "Transform.h"
#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"
#include "Engine.h"
#include "StageData.h"
#include "SceneData.h"

ChapterScene::ChapterScene()
{
}

ChapterScene::~ChapterScene()
{
}

void ChapterScene::OnStart()
{
	chapters.push_back(new ChapterChoice(1, std::string("Resources/Sprites/UIs/Chapters/chapter1.png"), this));
	chapters.push_back(new ChapterChoice(2, std::string("Resources/Sprites/UIs/Chapters/chapter2.png"), this));
	chapters.push_back(new ChapterChoice(3, std::string("Resources/Sprites/UIs/Chapters/chapter3.png"), this));
	chapters.push_back(new ChapterChoice(4, std::string("Resources/Sprites/UIs/Chapters/chapter4.png"), this));
	chapters.push_back(new ChapterChoice(5, std::string("Resources/Sprites/UIs/Chapters/chapter5.png"), this));
	chapters.push_back(new ChapterChoice(6, std::string("Resources/Sprites/UIs/Chapters/chapter6.png"), this));

	for (auto iter : chapters)
	{
		AttachObject(iter);
	}

	if (SceneData::GetInstance()->isFirst)
	{
		SceneData::GetInstance()->isFirst = false;

		AttachObject(new Pen1(true));
		AttachObject(new Pen2(true));
		AttachObject(new Pen3(true));
		AttachObject(new Ruler1(true));
		AttachObject(new Ruler2(true));
	}
	else
	{
		AttachObject(new Pen1(false));
		AttachObject(new Pen2(false));
		AttachObject(new Pen3(false));
		AttachObject(new Ruler1(false));
		AttachObject(new Ruler2(false));
	}
}

void ChapterScene::OnUpdate()
{
	time += RG2R_TimeM->GetDeltaTime();

	if (!isFinish && time >= 1.7f)
	{
		float max = RG2R_WindowM->GetSize().width;
		float now = RG2R_InputM->GetMousePos().x;

		if (now <= max * 0.3f)
		{
			float movePow = now / max;
			movePow = 0.3f - movePow;
			GetMainCamera()->Translate(movePow * -RG2R_TimeM->GetDeltaTime() * 30, 0);
		}
		if (now >= max * 0.7f)
		{
			float movePow = 1 - now / max;
			movePow = 0.3f - movePow;
			GetMainCamera()->Translate(movePow * RG2R_TimeM->GetDeltaTime() * 30, 0);
		}

		if (GetMainCamera()->GetPos().x <= 0)
			GetMainCamera()->SetPosX(0);
		else if (GetMainCamera()->GetPos().x >= 3.5f * (6 - 3))
			GetMainCamera()->SetPosX(3.5f * (6 - 3));
	}
}

void ChapterScene::ChoiceChapter()
{
	if (!isFinish)
	{
		isFinish = true;

		for (auto iter : chapters)
		{
			if (iter->chapter != StageData::GetInstance()->chapter)
				iter->MoveDown();
			else
				iter->GoStageScene();
		}
	}
}