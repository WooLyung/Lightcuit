#pragma once
#include "Scene.h"
#include "Gate.h"
#include "Line.h"
#include "ColorSet.h"
#include "GameInputManager.h"
#include "ObjectManager.h"

class InGameScene :
	public Scene
{
	friend class GameInputManager;
	friend class ObjectManager;

private:
	GameInputManager* gameInputManager;
	ObjectManager* objectManager;

	void PushGate(Gate*);
	Vec2L GetTilePos();

public:
	InGameScene();
	~InGameScene();

	void OnStart();
	void OnUpdate();
};