#pragma once
#include "Object.h"
#include "ColorSet.h"
#include "InGameScene.h"

class InGameScene;

class ObjectManager :
	public Object
{
	friend class GameInputManager;
	friend class PlayManager;

private:
	InGameScene* scene;

	std::vector<Gate*> gates;
	std::vector<Line*> connectingLine;
	std::list<Line*> lines;

public:
	ObjectManager(InGameScene*);
	~ObjectManager();

	void OnStart();

	void SetSpriteOnConnect(Line*, Line*, Vec2L);
	void SetSpriteOnFinish(Line*, Vec2L);
	void PushGate(Gate*);
};