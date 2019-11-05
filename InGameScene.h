#pragma once
#include "Scene.h"
#include "Gate.h"
#include "Line.h"
#include "ColorSet.h"
#include "GameInputManager.h"
#include "ObjectManager.h"
#include "PlayManager.h"
#include "Tiles.h"
#include "PlayButton.h"
#include <map>

class InGameScene :
	public Scene
{
	friend class GameInputManager;
	friend class ObjectManager;
	friend class PlayManager;
	friend class PlayButton;

private:
	GameInputManager* gameInputManager;
	ObjectManager* objectManager;
	PlayManager* playManager;
	Vec2L mapSize;
	Tiles* tiles;

	void PushGate(Gate*);
	void Init();
	void CreateGate(std::map<std::string, std::string>);
	Vec2L GetTilePos();

public:
	InGameScene();
	~InGameScene();

	void OnStart();
	void OnUpdate();
};