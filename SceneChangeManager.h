#pragma once
#include "Object.h"
#include "InGameScene.h"

class SceneChangeManager :
	public Object
{
private:
	InGameScene* scene;

	CommandList* toInGameScene;
	CommandList* toStageScene;

public:
	SceneChangeManager(InGameScene*);
	~SceneChangeManager();

	void Reset();
	void Back();
	void Diff();
};