#pragma once
#include "Object.h"
#include "ChapterScene.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Effect.h"

class SettingBoard :
	public Object
{
private:
	enum InputState {
		hover, click, none
	};

	InputState inputState = InputState::none;
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	ChapterScene* scene;

	float time = 0;
	CommandList* appearAnim, *disappearAnim;

	Object* blur;
	Effect* blurEffect;

public:
	enum BoardState {
		appear, wait, disappear, top
	};

	BoardState boardState = BoardState::top;
	CommandList* changeScene;

	SettingBoard(ChapterScene*);
	~SettingBoard();

	void OnStart();
	void OnUpdate();
	void Input();
};