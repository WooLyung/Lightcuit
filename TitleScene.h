#pragma once
#include "Scene.h"
#include "Title.h"

class TitleScene
	: public Scene
{
private:
	Title* title;
	float time = 0;

public:
	TitleScene();
	~TitleScene();

	void OnStart();
	void OnUpdate();
};