#pragma once
#include "Scene.h"
#include "Gate.h"
#include "Line.h"
#include "ColorSet.h"

class InGameScene :
	public Scene
{
private:
	enum InputState {
		NONE,
		GATE_LIFT,
		LINE_START,
		LINE_CONNECT,
		COLOR_CHANGE
	};

	InputState inputState = NONE;
	Gate* myGate = nullptr;
	Gate* targetGate = nullptr;

	// 오브젝트 목록
	std::vector<Gate*> gates;
	std::vector<Line*> connectingLine;
	ColorSet* colorSet;

	void PushGate(Gate*);
	void Input();
	void GateMove();
	void LineConnect();
	void LineUnconnect(Gate*);
	void LineCancel();
	void SetSpriteOnConnect(Line*, Line*, Vec2L);
	void SetSpriteOnFinish(Line*, Vec2L);
	Vec2L GetTilePos();

public:
	InGameScene();
	~InGameScene();

	void OnStart();
	void OnUpdate();
};