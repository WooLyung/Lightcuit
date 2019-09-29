#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "TestScene.h"

Scene* SceneManager::FirstScene()
{
	Scene* scene = new Scene();
	scene->onUpdateListener = [=]() {
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
			RG2R_SceneM->ChangeScene(scenes->operator[](0));
	};

	scenes->push_back(new TestScene);
	scenes->push_back(scene);

	return scenes->operator[](0);
}

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
			ApplyListener(registeredScene->onStartListener);
			registeredScene->OnStart();

			ApplyListener(registeredScene->onFirstUpdateBeforeListener);
			registeredScene->OnFirstUpdateBefore();
		}
		ApplyListener(registeredScene->onUpdateBeforeListener);
		registeredScene->OnUpdateBefore();

		registeredScene->Update();

		if (registeredScene->GetIsFirstUpdate())
		{
			ApplyListener(registeredScene->onFirstUpdateListener);
			registeredScene->OnFirstUpdate();

			registeredScene->isFirstUpdate = false;
		}
		ApplyListener(registeredScene->onUpdateListener);
		registeredScene->OnUpdate();

		registeredScene->state = SceneState::SCENE_ALIVE;
	}
}

void SceneManager::Render()
{
	if (registeredScene != nullptr)
	{
		if (registeredScene->GetIsFirstRender()) 
		{
			ApplyListener(registeredScene->onFirstRenderBeforeListener);
			registeredScene->OnFirstRenderBefore();
		}
		ApplyListener(registeredScene->onRenderBeforeListener);
		registeredScene->OnRenderBefore();

		registeredScene->Render();

		if (registeredScene->GetIsFirstRender())
		{
			ApplyListener(registeredScene->onFirstRenderListener);
			registeredScene->OnFirstRender();

			registeredScene->isFirstRender = false;
		}
		ApplyListener(registeredScene->onRenderListener);
		registeredScene->OnRender();
	}
}

void SceneManager::Render(ViewRenderData& viewRenderData)
{
	if (registeredScene != nullptr)
	{
		registeredScene->Render(viewRenderData);
	}
}

Scene* SceneManager::ChangeScene(Scene* newScene)
{	
	Scene* preScene = registeredScene;
	registeredScene = newScene;

	if (preScene != nullptr)
	{
		preScene->state = SceneState::SCENE_UNREGISTERED;
		ApplyListener(preScene->onFinishListener);
		preScene->OnFinish();
	}

	newScene->state = SceneState::SCENE_START;
	if (newScene->GetIsFirstRegister())
	{
		ApplyListener(newScene->onFirstRegisterListener);
		newScene->OnFirstRegister();

		newScene->isFirstRegister = false;
	}
	ApplyListener(newScene->onRegisterListener);
	newScene->OnRegister();

	return preScene;
}