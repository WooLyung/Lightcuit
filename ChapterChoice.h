#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "ChapterScene.h"

class ChapterScene;

class ChapterChoice :
	public Object
{
private:
	enum ChapterState {
		appear, wait, disappeard, wait2
	};

	enum InputState {
		hover, click, none
	};

	std::string path;
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	ChapterScene* scene;

	Transform* transform_child;
	SpriteRenderer* spriteRenderer_child;

	ChapterState state = appear;
	InputState inputState = InputState::none;

	// animations
	float animTime = 0;
	int inFlag = 1;
	int sizeFlag = 1;
	float fromX = 0;
	CommandList* appearAnim;
	CommandList* moveIn;
	CommandList* moveDown;
	CommandList* goStageScene;
	CommandList* changeScale;

	void Input();

public:
	int chapter = 0;

	ChapterChoice(int, std::string, ChapterScene*);
	~ChapterChoice();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void MoveDown();
	void GoStageScene();
};