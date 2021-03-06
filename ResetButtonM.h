#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "TextRenderer.h"
#include "MapCreateScene.h"

class MapCreateScene;

class ResetButtonM :
	public Object
{
private:
	enum InputState {
		hover, click, none
	};

	MapCreateScene* scene;

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	InputState inputState = none;

	// animations
	bool isAnim = false;
	float animTime = 0;
	int hoverFlag = 1, sizeFlag = 1;
	CommandList* appearAnim;
	CommandList* disappearAnim;
	CommandList* hoverAnim;
	CommandList* changeScale;

public:
	ResetButtonM(bool, MapCreateScene* scene);
	~ResetButtonM();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Input();
	void Disappear();
};