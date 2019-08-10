#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "Transform.h"
#include "TestObject.h"
#include "SpriteRenderer.h"

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

Scene* SceneManager::FirstScene()
{
	auto scene = new Scene();
	scene->onUpdateListener = [=]() {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_F11) == KeyState::KEYSTATE_ENTER)
		{
			RG2R_WindowM->ToggleFullscreen(); // F11로 전체화면
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_F4) == KeyState::KEYSTATE_ENTER 
			&& RG2R_InputM->GetKeyState(KeyCode::KEY_LALT) == KeyState::KEYSTATE_STAY)
		{
			RG2R_WindowM->Close(); // Alt + F4로 끄기
		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_STAY)
		{
			scene->GetMainCamera()->SetPosX(scene->GetMainCamera()->GetPos().x - RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY)
		{
			scene->GetMainCamera()->SetPosX(scene->GetMainCamera()->GetPos().x + RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_STAY)
		{
			scene->GetMainCamera()->SetPosY(scene->GetMainCamera()->GetPos().y + RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_STAY)
		{
			scene->GetMainCamera()->SetPosY(scene->GetMainCamera()->GetPos().y - RG2R_TimeM->GetDeltaTime() * 5);
		}
	};

	scene->AttachObject(new TestObject(0));

	return scene;
}