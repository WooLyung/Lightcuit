#pragma once
#include "stdafx.h"
#include "Scene.h"

class Scene;

class SceneManager
{
private:
	Scene* registeredScene = nullptr;
	std::vector<Scene*>* scenes = nullptr;

public:
	SceneManager();
	~SceneManager();

	void Update();
	void Render();
	Scene* FirstScene();
	Scene* ChangeScene(Scene*);

	std::vector<Scene*>* GetScenes() { return scenes; }
	Scene* GetScene() { return registeredScene; };
};