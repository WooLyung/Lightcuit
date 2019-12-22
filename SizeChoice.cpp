#include "stdafx.h"
#include "SizeChoice.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"
#include "Settings.h"

SizeChoice::SizeChoice(Vec2L size, std::string path, MapEditorScene* scene, Vec2F pos)
{
	this->size = size;
	this->path = path;
	this->scene = scene;
	this->pos = pos;
}

SizeChoice::~SizeChoice()
{
}

void SizeChoice::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture(path)
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-2);
	transform = GetComponent<Transform>()
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f)
		->SetPos(pos);

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
		transform->SetScale(Vec2F(transform->GetScale()) + Vec2F(1, 1) * RG2R_TimeM->GetDeltaTime() * 0.7f * sizeFlag);

		if (transform->GetScale().x > 0.3f)
		{
			transform->SetScale(0.7f, 0.7f);
			changeScale->Stop();
		}
		else if (transform->GetScale().x < 0.6f)
		{
			transform->SetScale(0.6f, 0.6f);
			changeScale->Stop();
		}
		}, 0);
	changeScale->SetIsLoop(true);
}

void SizeChoice::OnUpdate()
{
	Input();
}

void SizeChoice::Input()
{
	Vec2F vec = RG2R_InputM->GetMousePos() - (transform->GetScreenPos() + Vec2F(-6.5f * 0.8f, 0));

	if (vec.Dot(vec) <= sqrtf((float)(RG2R_WindowM->GetSize().width * RG2R_WindowM->GetSize().width + RG2R_WindowM->GetSize().height * RG2R_WindowM->GetSize().height)) * 0.2f)
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
				cout << "Å¬¸¯" << endl;
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

Transform* SizeChoice::GetTransform()
{
	return transform;
}

SpriteRenderer* SizeChoice::GetSpriteRenderer()
{
	return spriteRenderer;
}