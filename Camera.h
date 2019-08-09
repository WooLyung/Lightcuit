#pragma once
#include "Scene.h"

class Scene;

class Camera
{
private:
	Scene* scene = nullptr;
	std::string name = "";

	friend class Scene;

public:
	Camera();
	~Camera();

	std::string GetName(); // 태그 얻기
	Scene* GetScene(); // 씬 얻기
};