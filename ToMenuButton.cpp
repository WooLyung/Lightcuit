#include "stdafx.h"
#include "ToMenuButton.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"
#include "SceneData.h"
#include "ChapterScene.h"

ToMenuButton::ToMenuButton(InGameScene* scene, StageClearObj* clearObj)
{
	this->scene = scene;
	this->clearObj = clearObj;

	GetComponent<Transform>()->SetPos(50, 50);
}

ToMenuButton::~ToMenuButton()
{
}

void ToMenuButton::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Clear/toMenu.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-1);
	transform = GetComponent<Transform>()
		->SetScale(0.5f, 0.5f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetIsRelative(false);

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
}

void ToMenuButton::OnUpdate()
{
	transform->SetPos(parentTransform->GetPos() + Vec2F(0.4f, -1.4f));
	Input();

	if (changeTime >= 0)
	{
		changeTime += RG2R_TimeM->GetDeltaTime();
		if (changeTime >= 1.2f)
			RG2R_SceneM->ChangeScene(new ChapterScene, true);
	}
}

void ToMenuButton::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos()) - transform->GetPos();

	if (vec.Dot(vec) <= 0.06f)
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
				sizeFlag = 1;
				changeScale->Start();
				clearObj->Disappear();
				
				changeTime = 0;
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

Transform* ToMenuButton::GetTransform()
{
	return transform;
}

SpriteRenderer* ToMenuButton::GetSpriteRenderer()
{
	return spriteRenderer;
}