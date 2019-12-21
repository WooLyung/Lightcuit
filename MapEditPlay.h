#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "CommandList.h"
#include "MapEditorScene.h"

class MapEditorScene;

class MapEditPlay :
	public Object
{
private:
	enum StageState {
		appear, wait, disappear, wait2
	};

	Transform* transform;
	SpriteRenderer* spriteRenderer;
	MapEditorScene* scene;

	StageState state = appear;

	// animations
	float animTime = 0;
	CommandList* appearAnim;
	CommandList* disappearAnim;

public:
	MapEditPlay(MapEditorScene*);
	~MapEditPlay();

	Transform* GetTransform();
	SpriteRenderer* GetSpriteRenderer();

	void OnStart();
	void OnUpdate();
	void Disappear();
};