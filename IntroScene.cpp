#include "stdafx.h"
#include "IntroScene.h"
#include "IntroManager.h"
#include "Cursor.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::OnStart()
{
	AttachObject(new Cursor);
	AttachObject(new IntroManager);
}