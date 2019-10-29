#pragma once
#include "Object.h"
#include "InGameScene.h"
#include "Line.h"
#include "Gate.h"

class InGameScene;

struct Node
{
	Line* line;
	Gate* gate;
	int type = 0;
	std::vector<Node*> next;

	int inDegree = 0;
};

class PlayManager :
	public Object
{
private:
	enum GameState {
		CircuitDesign,
		Try,
		Clear,
	};

	InGameScene* scene;
	std::vector<Node*> sortedNodes;
	GameState gameState = CircuitDesign;

public:
	PlayManager(InGameScene*);
	~PlayManager();

	void OnUpdate();

	int CheckClear();
};