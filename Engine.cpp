#include "stdafx.h"
#include "Engine.h"

Engine::Engine()
{
}

Engine::~Engine()
{
}

Engine* Engine::GetInstance()
{
	static Engine instance_ = Engine();
	return &instance_;
}

void Engine::Init()
{
	windowM = new WindowManager();
	graphicM = new GraphicManager();
	inputM = new InputManager();
	soundM = new SoundManager();
	textureM = new TextureManager();
	timeM = new TimeManager();
}

void Engine::MainLoop()
{
	std::cout << "TEST" << std::endl;

	while (GetWindowM()->IsRunning())
	{
		// 타이머 틱 실행
		timeM->Tick();
		if (GetWindowM()->MsgLoop())
		{

		}

		// 매니저들과 인풋 업데이트
		soundM->Update();
		textureM->Update();
		inputM->Update();

		// 그래픽 렌더링
		graphicM->Render();
		}
}

void Engine::Release()
{
	SafeDelete(graphicM);
	SafeDelete(inputM);
	SafeDelete(soundM);
	SafeDelete(textureM);
	SafeDelete(timeM);
	SafeDelete(windowM);
}