#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"

class ChapterChoice :
	public Object
{
private:
	enum ChapterState {
		appear, wait, disappear
	};

	enum InputState {
		hover, click, none
	};

	std::string path;
	int chapter = 0;
	Transform* transform;
	SpriteRenderer* spriteRenderer;

	Transform* transform_child;
	SpriteRenderer* spriteRenderer_child;

	ChapterState state = appear;
	InputState inputState = InputState::none;

	// animations
	float animTime = 0;
	int inFlag = 1;
	int sizeFlag = 1;
	CommandList* appearAnim;
	CommandList* moveIn;
	CommandList* changeScale;

	void Input();

public:
	ChapterChoice(int, std::string);
	~ChapterChoice();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};