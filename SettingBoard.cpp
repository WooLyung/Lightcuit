#include "stdafx.h"
#include "SettingBoard.h"
#include "Engine.h"
#include "ViewRenderer.h"
#include "Settings.h"

SettingBoard::SettingBoard(ChapterScene* scene)
{
	this->scene = scene;
}

SettingBoard::~SettingBoard()
{
}

void SettingBoard::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Settings/setting_board.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(41);
	transform = GetComponent<Transform>()
		->SetScale(0.6f, 0.6f)
		->SetIsRelative(false)
		->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height - 0.65f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		time += RG2R_TimeM->GetDeltaTime() * 1.5f;
		transform->SetPosY((GetScene()->GetMainCamera()->GetCameraDefaultSize().height - 0.65f)
			* (time - 1) * (time - 1));

		blurEffect->ClearEffectInfo()
			->PushEffectInfo(new GaussianBlurEffectInfo(time * 2.5f))
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(1 - time * 0.2f, 1 - time * 0.2f, 1 - time * 0.2f)));

		if (time >= 1)
		{
			boardState = BoardState::wait;
			time = 0;
			appearAnim->Stop();
			transform->SetPosY(0);
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		time += RG2R_TimeM->GetDeltaTime() * 1.5f;
		transform->SetPosY((GetScene()->GetMainCamera()->GetCameraDefaultSize().height - 0.65f)
			* time * time);

		blurEffect->ClearEffectInfo()
			->PushEffectInfo(new GaussianBlurEffectInfo((1 - time) * 2.5f))
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(time * 0.2f + 0.8f, time * 0.2f + 0.8f, time * 0.2f + 0.8f)));

		if (time >= 1)
		{
			boardState = BoardState::top;
			time = 0;
			disappearAnim->Stop();
			transform->SetPosY(GetScene()->GetMainCamera()->GetCameraDefaultSize().height - 0.65f);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);

	blur = CreateObject();
	blurEffect = blur->AttachComponent<Effect>();

	blur->GetComponent<Transform>()
		->SetIsRelative(false)
		->SetAnchor(INCH_PER_DISTANCE * 8, INCH_PER_DISTANCE * 4);
	auto view = blur->AttachComponent<ViewRenderer>()
		->SetCamera(GetScene()->GetMainCamera())
		->SetSize(Size2U(INCH_PER_DISTANCE * 16, INCH_PER_DISTANCE * 8));
	view->SetZ_index(40);
}

void SettingBoard::OnUpdate()
{
	Input();
}


void SettingBoard::Input()
{
	Vec2F vec = RG2R_InputM->FromScreenToUI(RG2R_InputM->GetMousePos());

	if (boardState == BoardState::top
		&& vec.y >= transform->GetPos().y - 2.7f
		&& vec.y <= transform->GetPos().y - 2)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_NONE)
		{
			if (inputState == InputState::none)
			{
				inputState = InputState::hover;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
		{
			if (inputState == InputState::hover)
			{
				inputState = InputState::click;
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (inputState == InputState::click)
			{
				appearAnim->Start();
				boardState = BoardState::appear;
			}
		}
	}
	else
	{
		inputState = InputState::none;
	}

	if (boardState == BoardState::wait
		&& RG2R_InputM->GetKeyState(KeyCode::KEY_ESCAPE) == KeyState::KEYSTATE_ENTER)
	{
		disappearAnim->Start();
		boardState = BoardState::disappear;
	}
}