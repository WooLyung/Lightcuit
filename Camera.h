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

	std::string GetName(); // �±� ���
	Scene* GetScene(); // �� ���
};