#pragma once
#include "Scene.h"
#include "Gate.h"
#include "Line.h"
#include "ColorSet.h"
#include "GameInputManager.h"
#include "ObjectManager.h"
#include "PlayManager.h"

class InGameScene :
	public Scene
{
	friend class GameInputManager;
	friend class ObjectManager;
	friend class PlayManager;

private:
	GameInputManager* gameInputManager;
	ObjectManager* objectManager;
	PlayManager* playManager;

	void PushGate(Gate*);
	Vec2L GetTilePos();

public:
	InGameScene();
	~InGameScene();

	void OnStart();
	void OnUpdate();
};