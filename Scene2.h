#pragma once
#include "Scene.h"
class Scene2 :
	public Scene
{
public:
	Scene2();
	~Scene2();

	void OnUpdate();
	void OnDestroy();
};