#include "stdafx.h"
#include "MenuButtonM.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

MenuButtonM::MenuButtonM(bool isAnim, MapCreateScene* scene)
{
	this->isAnim = isAnim;
	this->scene = scene;
}

MenuButtonM::~MenuButtonM()
{
}

void MenuButtonM::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Menus/menuButton.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.2f, 0.2f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetIsRelative(false);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			appearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.5f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f + pow(animTime - 1, 2) * 5);
		transform->SetRot(250 - (pow(animTime - 1, 2) + 1) * 250);
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();

		if (animTime >= 1)
		{
			animTime = 1;
			disappearAnim->Stop();
		}

		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.5f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f + pow(animTime, 2) * 5);
		transform->SetRot(pow(animTime, 2) * 250);
		}, 0);
	disappearAnim->SetIsLoop(true);

	hoverAnim = new CommandList;
	commandLists.push_back(hoverAnim);
	hoverAnim->PushCommand([=]() {
		transform->SetRot(transform->GetRot() + RG2R_TimeM->GetDeltaTime() * hoverFlag * 100);

		if (transform->GetRot() > 8)
		{
			transform->SetRot(8);
			hoverAnim->Stop();
		}
		else if (transform->GetRot() < 0)
		{
			transform->SetRot(0);
			hoverAnim->Stop();
		}
		}, 0);
	hoverAnim->SetIsLoop(true);

	changeScale = new CommandList;
	commandLists.push_back(changeScale);
	changeScale->PushCommand([=]() {
		transform->SetScale(Vec2F(transform->GetScale()) + Vec2F(1, 1) * RG2R_TimeM->GetDeltaTime() * 0.3f * sizeFlag);

		if (transform->GetScale().x > 0.2f)
		{
			transform->SetScale(0.2f, 0.2f);
			changeScale->Stop();
		}
		else if (transform->GetScale().x < 0.18f)
		{
			transform->SetScale(0.18f, 0.18f);
			changeScale->Stop();
		}
		}, 0);
	changeScale->SetIsLoop(true);

	if (!isAnim)
	{
		animTime = 1;
		transform->SetPos(GetScene()->GetMainCamera()->GetCameraDefaultSize().width * 0.5f - 0.5f,
			GetScene()->GetMainCamera()->GetCameraDefaultSize().height * 0.5f - 0.5f + pow(animTime - 1, 2) * 5);
		transform->SetRot(50 - (pow(animTime - 1, 2) + 1) * 50);
	}
}

void MenuButtonM::OnUpdate()
{
	Input();
}

void MenuButtonM::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos()) - transform->GetPos();

	if (vec.Dot(vec) <= 0.1f)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
				hoverFlag = 1;
				hoverAnim->Start();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
				sizeFlag = -1;
				changeScale->Start();
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				inputState = InputState::none;
				sizeFlag = 1;
				changeScale->Start();

				scene->Disappear(3);
			}
		}
	}
	else
	{
		inputState = InputState::none;
		hoverFlag = -1;
		hoverAnim->Start();

		sizeFlag = 1;
		changeScale->Start();
	}
}

Transform* MenuButtonM::GetTransform()
{
	return transform;
}

SpriteRenderer* MenuButtonM::GetSpriteRenderer()
{
	return spriteRenderer;
}

void MenuButtonM::Disappear()
{
	disappearAnim->Start();
	animTime = 0;
}