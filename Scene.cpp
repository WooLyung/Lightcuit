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

	// ������Ʈ �߰��� ������ �߰��ؾ���

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
	return nullptr; // ��������
}

Object* Scene::FindObject(const Object*)
{
	return nullptr; // ��������
}

Object* Scene::FindObjectByTag(const std::string)
{
	return nullptr; // ��������
}

Object* Scene::FindObjectByName(const std::string)
{
	return nullptr; // ��������
}

Object* Scene::FindObjectCondition(std::function<bool(const Object*)>)
{
	return nullptr; // ��������
}

std::vector<Object*> Scene::FindObjectsByTag(const std::string)
{
	return std::vector<Object*>(); // ��������
}

std::vector<Object*> Scene::FindObjectsByName(const std::string)
{
	return std::vector<Object*>(); // ��������
}

std::vector<Object*> Scene::FindObjectsCondition(std::function<bool(const Object*)>)
{
	return std::vector<Object*>(); // ��������
}

Camera* Scene::CreateCamera()
{
	return nullptr; // ��������
}

Camera* Scene::FindCamera(const Camera*)
{
	return nullptr; // ��������
}

Camera* Scene::FindCameraByName(const std::string)
{
	return nullptr; // ��������
}

Camera* Scene::FindCameraCondition(std::function<bool(const Camera*)>)
{
	return nullptr; // ��������
}

std::vector<Camera*> Scene::FindCamerasCondition(std::function<bool(const Camera*)>)
{
	return std::vector<Camera*>(); // ��������
}

ObjectBuilder* Scene::CreateObjectBuilder()
{
	return nullptr; // ��������
}

CameraBuilder* Scene::CreateCameraBuilder()
{
	return nullptr; // ��������
}