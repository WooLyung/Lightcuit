#include "stdafx.h"
#include "IntroScene.h"
#include "IntroManager.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
}

void IntroScene::OnStart()
{
	AttachObject(new IntroManager);
}