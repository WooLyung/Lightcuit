#pragma once
#include "stdafx.h"
#include "Scene.h"
#include "ViewRenderData.h"

class Scene;
class ViewRenderData;

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
	void Render(ViewRenderData&);

	Scene* FirstScene();
	Scene* ChangeScene(Scene*);

	std::vector<Scene*>* GetScenes() { return scenes; }
	Scene* GetScene() { return registeredScene; };
};