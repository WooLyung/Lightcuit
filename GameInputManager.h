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
	InGameScene* scene;

	InputState inputState = NONE;
	Gate* myGate = nullptr;
	Gate* targetGate = nullptr;

	ColorSet* colorSet;

public:
	GameInputManager(InGameScene*);
	~GameInputManager();

	void OnUpdate();
	void OnStart();

	void Input();
	void GateMove();
	void LineConnect();
	void LineUnconnect(Gate*);
	void LineCancel();
};