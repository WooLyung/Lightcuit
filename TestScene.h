#pragma once
#include "Scene.h"
#include <iostream>

class TestScene :
	public Scene
{
public:
	TestScene();
	~TestScene();
	void OnStart();
	void OnUpdate();
};