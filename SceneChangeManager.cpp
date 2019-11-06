#include "stdafx.h"
#include "SceneChangeManager.h"
#include "Engine.h"
#include "ChapterScene.h"
#include "SceneData.h"

SceneChangeManager::SceneChangeManager(InGameScene* scene)
{
	this->scene = scene;

	toInGameScene = new CommandList;
	toInGameScene->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new InGameScene, true);
		}, 1.2f);
	commandLists.push_back(toInGameScene);

	toStageScene = new CommandList;
	toStageScene->PushCommand([=]() {
		SceneData::GetInstance()->isFirst = false;
		RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}, 1.2f);
	commandLists.push_back(toStageScene);
}

SceneChangeManager::~SceneChangeManager()
{
}

void SceneChangeManager::Reset()
{
	toInGameScene->Start();
}

void SceneChangeManager::Back()
{
	toStageScene->Start();
}

void SceneChangeManager::Diff()
{
	toInGameScene->Start();
}