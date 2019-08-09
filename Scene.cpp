#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
	objectBuilder = new ObjectBuilder;
	cameraBuilder = new CameraBuilder;

	OnCreate();
}

Scene::~Scene()
{
	ApplyListener(onDestroyListener);
	OnDestroy();

	for (auto iter : objects)
	{
		delete iter;
	}

	delete cameraBuilder;
	delete objectBuilder;
}

void Scene::Update()
{
	for (auto iter : objects)
	{
		if (iter->isFirstUpdate)
		{
			ApplyListener(iter->onFirstUpdateBeforeListener);
			iter->OnFirstUpdateBefore();
		}
		ApplyListener(iter->onUpdateBeforeListener);
		iter->OnUpdateBefore();

		iter->Update();

		if (iter->isFirstUpdate)
		{
			ApplyListener(iter->onFirstUpdateListener);
			iter->OnFirstUpdate();

			iter->isFirstUpdate = false;
		}
		ApplyListener(iter->onUpdateListener);
		iter->OnUpdate();
	}
}

void Scene::Render()
{
	for (auto iter : objects)
	{
		if (iter->isFirstRender)
		{
			ApplyListener(iter->onFirstRenderBeforeListener);
			iter->OnFirstRenderBefore();
		}
		ApplyListener(iter->onRenderBeforeListener);
		iter->OnRenderBefore();

		iter->Render();

		if (iter->isFirstRender)
		{
			ApplyListener(iter->onFirstRenderListener);
			iter->OnFirstRender();

			iter->isFirstRender = false;
		}
		ApplyListener(iter->onRenderListener);
		iter->OnRender();
	}
}

Object* Scene::CreateObject()
{
	return nullptr; // ��������
}

Object* Scene::AttachObject(Object* object)
{
	if (object->scene != this)
	{
		object->scene = this;
		objects.push_back(object);
	}

	return object;
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

Camera* Scene::AttachCamera(Camera*)
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