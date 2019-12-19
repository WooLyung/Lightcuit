#pragma once
#include "Scene.h"
#include "ChapterChoice.h"
#include "GoMapEditor.h"

class ChapterChoice;
class GoMapEditor;

class ChapterScene :
	public Scene
{
private:
	std::list<ChapterChoice*> chapters;
	GoMapEditor* goMapEditor = nullptr;
	float time = 0;

public:
	bool isFinish = false;

	ChapterScene();
	~ChapterScene();

	void OnStart();
	void OnUpdate();
	void ChoiceChapter();
};