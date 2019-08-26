#include "stdafx.h"
#include "Scene.h"
#include "Settings.h"
#include "Engine.h"
#include "ViewRenderer.h"

Scene::Scene()
{
	mainCamera = new Camera;
}

Scene::~Scene()
{
	ApplyListener(onDestroyListener);
	OnDestroy();

	for (auto iter : objects)
	{
		delete iter;
	}
	for (auto iter : cameras)
	{
		delete iter;
	}

	delete mainCamera;
}

void Scene::Update()
{
	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
		{
			if (iter->isFirstUpdate)
			{
				ApplyListener(iter->onStartListener);
				iter->OnStart();

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

	for (auto iter : cameras)
	{
		iter->Update();
	}
}

void Scene::Render()
{
	float translationRatio = sqrtf(
		(float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)
		/ (INCH_PER_DISTANCE * INCH_PER_DISTANCE * DIAGONAL_LENGTH * DIAGONAL_LENGTH)
	);

	defaultMatrix =
		D2D1::Matrix3x2F::Scale(translationRatio, translationRatio) *
		D2D1::Matrix3x2F(mainCamera->GetIsFlipX() ? -1 : 1, 0, 0, mainCamera->GetIsFlipY() ? -1 : 1, 0, 0) * 
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / 2.f, RG2R_WindowM->GetSize().height / 2.f);

	matrix =
		D2D1::Matrix3x2F::Scale(translationRatio, translationRatio) *
		D2D1::Matrix3x2F::Translation(-GetMainCamera()->GetPos().x * INCH_PER_DISTANCE, GetMainCamera()->GetPos().y * INCH_PER_DISTANCE)*
		D2D1::Matrix3x2F::Rotation(-GetMainCamera()->GetRot()) *
		D2D1::Matrix3x2F(mainCamera->GetIsFlipX() ? -1 : 1, 0, 0, mainCamera->GetIsFlipY() ? -1 : 1, 0, 0) * 
		D2D1::Matrix3x2F::Scale(GetMainCamera()->GetZoom().x, GetMainCamera()->GetZoom().y) *
		D2D1::Matrix3x2F::Translation(RG2R_WindowM->GetSize().width / 2.f, RG2R_WindowM->GetSize().height / 2.f);

	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
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
}

void Scene::Render(ViewRenderer* viewRenderer)
{
	defaultMatrix_v =
		D2D1::Matrix3x2F(viewRenderer->GetCamera()->GetIsFlipX() ? -1 : 1, 0, 0, viewRenderer->GetCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Translation(viewRenderer->GetSize().width / 2.f, viewRenderer->GetSize().height / 2.f);

	matrix_v =
		D2D1::Matrix3x2F::Translation(-viewRenderer->GetCamera()->GetPos().x * INCH_PER_DISTANCE, viewRenderer->GetCamera()->GetPos().y * INCH_PER_DISTANCE)*
		D2D1::Matrix3x2F::Rotation(-viewRenderer->GetCamera()->GetRot()) *
		D2D1::Matrix3x2F(viewRenderer->GetCamera()->GetIsFlipX() ? -1 : 1, 0, 0, viewRenderer->GetCamera()->GetIsFlipY() ? -1 : 1, 0, 0) *
		D2D1::Matrix3x2F::Scale(viewRenderer->GetCamera()->GetZoom().x, viewRenderer->GetCamera()->GetZoom().y) *
		D2D1::Matrix3x2F::Translation(viewRenderer->GetSize().width / 2.f, viewRenderer->GetSize().height / 2.f);

	for (auto iter : objects)
	{
		if (iter->GetIsEnable())
		{
			iter->Render(viewRenderer);
		}
	}
}

Object* Scene::CreateObject()
{
	auto object = new Object();
	AttachObject(object);

	return object;
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

Object* Scene::FindObject(const Object* object)
{
	for (auto iter : objects)
	{
		if (iter == object)
			return iter;

		auto result = iter->FindChild(object);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectByTag(const std::string tag)
{
	for (auto iter : objects)
	{
		if (iter->GetTag() == tag)
			return iter;

		auto result = iter->FindChildByTag(tag);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectByName(const std::string name)
{
	for (auto iter : objects)
	{
		if (iter->GetName() == name)
			return iter;

		auto result = iter->FindChildByName(name);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

Object* Scene::FindObjectCondition(std::function<bool(const Object*)> condition)
{
	for (auto iter : objects)
	{
		if (condition(iter))
			return iter;

		auto result = iter->FindChildCondition(condition);
		if (result != nullptr)
			return result;
	}

	return nullptr;
}

std::vector<Object*> Scene::FindObjectsByTag(const std::string tag)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (iter->GetTag() == tag)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByTag(tag);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Scene::FindObjectsByName(const std::string name)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (iter->GetName() == name)
			foundObjects.push_back(iter);

		auto result = iter->FindChildsByName(name);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

std::vector<Object*> Scene::FindObjectsCondition(std::function<bool(const Object*)> condition)
{
	std::vector<Object*> foundObjects;

	for (auto iter : objects)
	{
		if (condition(iter))
			foundObjects.push_back(iter);

		auto result = iter->FindChildsCondition(condition);
		for (auto iter2 : result)
			foundObjects.push_back(iter2);
	}

	return foundObjects;
}

Camera* Scene::CreateCamera()
{
	auto camera = new Camera();
	AttachCamera(camera);

	return camera;
}

Camera* Scene::AttachCamera(Camera* camera)
{
	if (camera->scene != this)
	{
		camera->scene = this;
		cameras.push_back(camera);
	}

	return camera;
}

Camera* Scene::FindCamera(const Camera* cam)
{
	for (auto iter : cameras)
	{
		if (iter == cam)
			return iter;
	}

	return nullptr;
}

Camera* Scene::FindCameraByName(const std::string name)
{
	for (auto iter : cameras)
	{
		if (iter->GetName() == name)
			return iter;
	}

	return nullptr;
}

Camera* Scene::FindCameraCondition(std::function<bool(const Camera*)> condition)
{
	for (auto iter : cameras)
	{
		if (condition(iter))
			return iter;
	}

	return nullptr;
}

std::vector<Camera*> Scene::FindCamerasCondition(std::function<bool(const Camera*)> condition)
{
	std::vector<Camera*> foundCameras;

	for (auto iter : cameras)
	{
		if (condition(iter))
			foundCameras.push_back(iter);
	}

	return foundCameras;
}