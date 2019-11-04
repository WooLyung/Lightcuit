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

	AttachObject(new Pen1);
	AttachObject(new Pen2);
	AttachObject(new Pen3);
	AttachObject(new Ruler1);
	AttachObject(new Ruler2);
}