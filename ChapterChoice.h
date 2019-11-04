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

	std::string path;
	Transform* transform;
	SpriteRenderer* spriteRenderer;
	int chapter = 0;
	ChapterState state = appear;

	// animations
	float animTime = 0;
	CommandList* appearAnim;

public:
	ChapterChoice(int, std::string);
	~ChapterChoice();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
};