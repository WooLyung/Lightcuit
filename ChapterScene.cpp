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
	AttachObject(new ChapterChoice(1, std::string("Resources/Sprites/UIs/Chapters/chapter1.png")));
	AttachObject(new ChapterChoice(2, std::string("Resources/Sprites/UIs/Chapters/chapter2.png")));
	AttachObject(new ChapterChoice(3, std::string("Resources/Sprites/UIs/Chapters/chapter3.png")));
}