#include "stdafx.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Engine.h"
#include "Transform.h"
#include "TestObject.h"
#include "SpriteRenderer.h"
#include "ViewRenderer.h"
#include "TextRenderer.h"
#include "TextRenderData.h"
#include "RandomGenerator.h"
#include "Command.h"
#include "CommandList.h"

Scene* SceneManager::FirstScene()
{
	auto scene = new Scene();
	auto scene2 = new Scene();

	scene->AttachObject(new TestObject(0));
	auto cam = scene->CreateCamera();
	auto view = scene->CreateObject()
		->AttachComponent<ViewRenderer>()
		->SetBackgroundColor(D2D1::ColorF(0xf07799ff))
		->SetCamera(cam)
		->SetSizeX(600)
		->SetSizeY(600)
		->GetOwner()
		->GetComponent<Transform>()
		->SetPos(2, 2)
		->SetScale(0.5f, 0.5f)
		->SetIsRelative(false)
		->GetOwner();

	auto commandList = new CommandList();
	commandList->PushCommand([=]() { std::cout << "1" << std::endl; }, 1);
	commandList->PushCommand([=]() { std::cout << "2" << std::endl; }, 1);
	commandList->PushCommand([=]() { std::cout << "3" << std::endl; }, 1);
	commandList->PushCommand([=]() { std::cout << "4" << std::endl; }, 1);
	commandList->SetIsLoop(true);

	view->commandLists.push_back(commandList);
	commandList->Start();

	scene->onUpdateListener = [=]() {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_F3) == KeyState::KEYSTATE_ENTER)
		{
			SoundOptions so;
			so.volume = 0.8f;
			so.pitch = 1.5f;
			so.isLoop = true;
			so.autoDelete = true;

			RG2R_SoundM->Play("Resources/Sounds/music.ogg");
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_F4) == KeyState::KEYSTATE_ENTER)
		{
			SoundOptions so;
			so.volume = 0.8f;
			so.pitch = 1.5f;
			so.isLoop = true;
			so.autoDelete = true;

			if (RG2R_SoundM->GetSound(0)->options.isMute)
			{
				so.isMute = false;
				RG2R_SoundM->SetOptions(0, so);
			}
			else
			{
				so.isMute = true;
				RG2R_SoundM->SetOptions(0, so);
			}
		}
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
			cam->SetPosX(cam->GetPos().x - RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY)
		{
			cam->SetPosX(cam->GetPos().x + RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_STAY)
		{
			cam->SetPosY(cam->GetPos().y + RG2R_TimeM->GetDeltaTime() * 5);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_STAY)
		{
			cam->SetPosY(cam->GetPos().y - RG2R_TimeM->GetDeltaTime() * 5);
		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_F) == KeyState::KEYSTATE_ENTER)
		{
			cam->SetIsFlipY(!cam->GetIsFlipY());
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_Q) == KeyState::KEYSTATE_STAY)
		{
			scene->GetMainCamera()->SetRot(scene->GetMainCamera()->GetRot() + RG2R_TimeM->GetDeltaTime() * -95);
		}
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_E) == KeyState::KEYSTATE_STAY)
		{
			cam->SetZoomX(cam->GetZoom().x + RG2R_TimeM->GetDeltaTime() * 0.5f);
			cam->SetZoomY(cam->GetZoom().y + RG2R_TimeM->GetDeltaTime() * 0.5f);
		}
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{

		}

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER)
		{
			RG2R_SceneM->ChangeScene(scene2);
		}
	};

	scene2->onUpdateListener = [=]() {
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER)
		{
			RG2R_SceneM->ChangeScene(scene);
		}
	};

	return scene;
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