#pragma once
#include "Scene.h"
#include "ChapterChoice.h"

class ChapterChoice;

class ChapterScene :
	public Scene
{
private:
	std::list<ChapterChoice*> chapters;
	float time = 0;

public:
	bool isFinish = false;

	ChapterScene();
	~ChapterScene();

	void OnStart();
	void OnUpdate();
	void ChoiceChapter();
};