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
	int inDegree = 0;
	std::vector<Node*> next;
};

class PlayManager :
	public Object
{
	friend class GameInputManager;

private:
	InGameScene* scene;
	std::vector<Node*> sortedNodes;
	GameState gameState = CircuitDesign;
	CommandList* tryPlay;
	int playIndex = 0;

public:
	PlayManager(InGameScene*);
	~PlayManager();

	void OnUpdate();
	void OnStart();

	int CheckClear();
	void Play();
};