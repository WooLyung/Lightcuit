#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
	scenes = new std::vector<Scene*>;
	ChangeScene(FirstScene());
}

SceneManager::~SceneManager()
{
	for (auto iter : *scenes)
		SafeDelete(iter);

	SafeDelete(scenes);
	if (registeredScene != nullptr)
		SafeDelete(registeredScene);
}

void SceneManager::Update()
{
	if (registeredScene != nullptr)
	{
		if (registeredScene->GetIsFirstUpdate())
		{
			if (registeredScene->onFirstUpdateBeforeListener != NULL)
				registeredScene->onFirstUpdateBeforeListener();
			registeredScene->OnFirstUpdateBefore();
		}
		if (registeredScene->onUpdateBeforeListener != NULL)
			registeredScene->onUpdateBeforeListener();
		registeredScene->OnUpdateBefore();

		registeredScene->Update();

		if (registeredScene->GetIsFirstUpdate())
		{
			if (registeredScene->onFirstUpdateListener != NULL)
				registeredScene->onFirstUpdateListener();
			registeredScene->OnFirstUpdate();

			registeredScene->isFirstUpdate = false;
		}
		if (registeredScene->onUpdateListener != NULL)
			registeredScene->onUpdateListener();
		registeredScene->OnUpdate();
	}
}

void SceneManager::Render()
{
	if (registeredScene != nullptr)
	{
		if (registeredScene->GetIsFirstRender()) 
		{
			if (registeredScene->onFirstRenderBeforeListener != NULL)
				registeredScene->onFirstRenderBeforeListener();
			registeredScene->OnFirstRenderBefore();
		}
		if (registeredScene->onRenderBeforeListener != NULL)
			registeredScene->onRenderBeforeListener();
		registeredScene->OnRenderBefore();

		registeredScene->Render();

		if (registeredScene->GetIsFirstRender())
		{
			if (registeredScene->onFirstRenderListener != NULL)
				registeredScene->onFirstRenderListener();
			registeredScene->OnFirstRender();

			registeredScene->isFirstRender = false;
		}
		if (registeredScene->onRenderListener != NULL)
			registeredScene->onRenderListener();
		registeredScene->OnRender();
	}
}

Scene* SceneManager::ChangeScene(Scene* newScene)
{	
	Scene* preScene = registeredScene;
	registeredScene = newScene;

	if (preScene != nullptr)
	{
		preScene->state = SCENE_STATE::UNREGISTERED;
		if (preScene->onFinishListener != NULL)
			preScene->onFinishListener();
		preScene->OnFinish();
	}

	newScene->state = SCENE_STATE::START;
	if (newScene->GetIsFirstRegister())
	{
		if (newScene->onFirstRegisterListener != NULL)
			newScene->onFirstRegisterListener();
		newScene->OnFirstRegister();

		newScene->isFirstRegister = false;
	}
	if (newScene->onRegisterListener != NULL)
		newScene->onRegisterListener();
	newScene->OnRegister();

	return preScene;
}

Scene* SceneManager::FirstScene()
{
	auto scene = new Scene();
	scene->onRegisterListener = [&]() { std::cout << "onRegister" << std::endl; };
	// 처음 시작하는 씬을 생성하고, 반환함

	return scene;
}