#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	OnCreate();
}

Scene::~Scene()
{
	if (onDestroyListener != NULL)
		onDestroyListener();
	OnDestroy();

	// 오브젝트 추가한 다음에 추가해야함

	SafeDelete(cameraBuilder);
	SafeDelete(objectBuilder);
}

void Scene::Update()
{

}

void Scene::Render()
{

}

Object* Scene::CreateObject()
{
	return nullptr; // 만들어야함
}

Object* Scene::FindObject(const Object*)
{
	return nullptr; // 만들어야함
}

Object* Scene::FindObjectByTag(const std::string)
{
	return nullptr; // 만들어야함
}

Object* Scene::FindObjectByName(const std::string)
{
	return nullptr; // 만들어야함
}

Object* Scene::FindObjectCondition(std::function<bool(const Object*)>)
{
	return nullptr; // 만들어야함
}

std::vector<Object*> Scene::FindObjectsByTag(const std::string)
{
	return std::vector<Object*>(); // 만들어야함
}

std::vector<Object*> Scene::FindObjectsByName(const std::string)
{
	return std::vector<Object*>(); // 만들어야함
}

std::vector<Object*> Scene::FindObjectsCondition(std::function<bool(const Object*)>)
{
	return std::vector<Object*>(); // 만들어야함
}

Camera* Scene::CreateCamera()
{
	return nullptr; // 만들어야함
}

Camera* Scene::FindCamera(const Camera*)
{
	return nullptr; // 만들어야함
}

Camera* Scene::FindCameraByName(const std::string)
{
	return nullptr; // 만들어야함
}

Camera* Scene::FindCameraCondition(std::function<bool(const Camera*)>)
{
	return nullptr; // 만들어야함
}

std::vector<Camera*> Scene::FindCamerasCondition(std::function<bool(const Camera*)>)
{
	return std::vector<Camera*>(); // 만들어야함
}

ObjectBuilder* Scene::CreateObjectBuilder()
{
	return nullptr; // 만들어야함
}

CameraBuilder* Scene::CreateCameraBuilder()
{
	return nullptr; // 만들어야함
}