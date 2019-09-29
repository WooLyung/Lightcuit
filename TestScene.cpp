#include "stdafx.h"
#include "TestScene.h"
#include "Object.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Transform.h"

void TestScene::OnUpdate() {
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_MBUTTON) == KeyState::KEYSTATE_ENTER)
		GetMainCamera()->SetPos(RG2R_InputM->GetMouseWorldPos());

	// Alt + F4 -> 프로그램 종료
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_LALT) == KeyState::KEYSTATE_STAY
		&& RG2R_InputM->GetKeyState(KeyCode::KEY_F4) == KeyState::KEYSTATE_ENTER)
		RG2R_WindowM->Close();

	// F11      -> 전체화면
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_F11) == KeyState::KEYSTATE_ENTER)
		RG2R_WindowM->ToggleFullscreen();
}

void TestScene::OnStart() {
	GetMainCamera()->SetRot(45);
	GetMainCamera()->SetZoom(Vec2F(0.5f, 0.5f));

	auto obj = CreateObject();
	auto spriteRenderer = obj->AttachComponent<SpriteRenderer>();
	spriteRenderer->SetTexture("Sprites/test.png");
	obj->GetComponent<Transform>()
		->SetAnchor(16, 16)
		->SetIsRelative(false); // 실제 이미지 픽셀 기준

	obj->onUpdateListener = [=]() {
		auto transform = obj->GetComponent<Transform>();

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_STAY)
			transform->SetPosY(transform->GetPos().y + RG2R_TimeM->GetDeltaTime() * 5);
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_S) == KeyState::KEYSTATE_STAY)
			transform->SetPosY(transform->GetPos().y - RG2R_TimeM->GetDeltaTime() * 5);
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_A) == KeyState::KEYSTATE_STAY)
			transform->SetPosX(transform->GetPos().x - RG2R_TimeM->GetDeltaTime() * 5);
		if (RG2R_InputM->GetKeyState(KeyCode::KEY_D) == KeyState::KEYSTATE_STAY)
			transform->SetPosX(transform->GetPos().x + RG2R_TimeM->GetDeltaTime() * 5);

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_Q) == KeyState::KEYSTATE_STAY)
			transform->SetRot(transform->GetRot() + 1);

		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_ENTER)
			RG2R_SceneM->ChangeScene(RG2R_SceneM->GetScenes()->operator[](1));

		if (RG2R_InputM->GetKeyState(KeyCode::KEY_T) == KeyState::KEYSTATE_STAY) {
			auto mousePos = RG2R_GraphicM->FromScreenToUI(RG2R_InputM->GetMousePos());
			auto vec = (mousePos - transform->GetPos()).Normalize();

			transform->Translate(vec.x * RG2R_TimeM->GetDeltaTime(), vec.y * RG2R_TimeM->GetDeltaTime());
		}
	};
}

TestScene::TestScene()
{
}

TestScene::~TestScene()
{
}
