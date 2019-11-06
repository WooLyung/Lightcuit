#pragma once
#include "Object.h"
#include "InGameScene.h"

class InGameScene;

class GameInputManager :
	public Object
{
public:
	enum InputState {
		NONE,
		GATE_LIFT,
		LINE_START,
		LINE_CONNECT,
		COLOR_CHANGE
	};

private:
	enum Directional {
		INPUT, OUTPUT, NO
	};

	InGameScene* scene;

	InputState inputState = NONE;
	Directional directional = NO;
	Gate* myGate = nullptr;
	Gate* targetGate = nullptr;
	Line* lastLine = nullptr;
	Vec2L tilePos;
	bool existGate = false;

public:
	GameInputManager(InGameScene*);
	~GameInputManager();

	void OnUpdate();
	void OnStart();

	Line* CreateLine(int, int);
	Line* CreateLine(int, int, Line*);

	void Input();
	void Input_Erase();
	void Input_Rotate();
	void Input_Select();
	void Input_Connect();

	void GateMove();
	void LineConnect();
	void CancelConnect();
	void Erase(Vec2L);
	void Erase(Gate*);
};