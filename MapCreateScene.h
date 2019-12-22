#pragma once
#include "Scene.h"
//#include "MapInputManager.h"
#include "SceneChangeManager2.h"
#include "Palette.h"
//#include "GateF.h"
#include "Tiles.h"
#include "Cursor.h"
#include <list>

#include "MenuButtonM.h"
#include "ResetButtonM.h"
#include "TryButtonM.h"

class MenuButtonM;
class ResetButtonM;
class TryButtonM;
class SceneChangeManager2;
class Palette;

class MapCreateScene :
	public Scene
{
private:
	//MapInputManager* mapInputManager;
	SceneChangeManager2* sceneChangeManager;

	Palette* palette;
	Tiles* tiles;
	MenuButtonM* menu;
	ResetButtonM* reset;
	TryButtonM* tryb;

	//list<GateF*> gates;

	bool isFinish = false;

	//void PushGateF(GateF*);
	Vec2L GetTilePos();

public:
	Cursor* cursor;

	MapCreateScene();
	~MapCreateScene();

	void OnStart();
	void OnUpdate();
	void Disappear(int);
};