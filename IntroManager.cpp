#include "stdafx.h"
#include "IntroManager.h"
#include "CommandList.h"
#include "Engine.h"
#include "ChapterScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"

IntroManager::IntroManager()
{
}

IntroManager::~IntroManager()
{
}

void IntroManager::OnStart()
{
	black = CreateObject();
	black->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/black.png")
		->SetZ_index(-1);
	black->GetComponent<Transform>()
		->SetAnchor(64, 36)
		->SetScale(15, 15);
	effect = black->AttachComponent<Effect>();

	textRenderer = AttachComponent<TextRenderer>()
		->SetText("적당한 인트로 글자입니다.")->SetTextColor(Color(1, 1, 1, 0))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);
}

void IntroManager::OnUpdate()
{
	time += RG2R_TimeM->GetDeltaTime();

	if (state == IntroState::firstWait)
	{
		if (time >= 1)
		{
			state = IntroState::appear1;
			time = 0;
		}
	}
	else if (state == IntroState::appear1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::wait1;
			time = 0;
		}
	}
	else if (state == IntroState::wait1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1));

		if (time >= 1.5f)
		{
			state = IntroState::disappear1;
			time = 0;
		}
	}
	else if (state == IntroState::disappear1)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1 - time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::textWait;
			time = 0;
		}
	}
	else if (state == IntroState::textWait)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 0));

		if (time >= 1.5f)
		{
			state = IntroState::appear2;
			textRenderer->SetText("적당한 두 번째 텍스트");
			time = 0;
		}
	}
	else if (state == IntroState::appear2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::wait2;
			time = 0;
		}
	}
	else if (state == IntroState::wait2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1));

		if (time >= 1.5f)
		{
			state = IntroState::disappear2;
			time = 0;
		}
	}
	else if (state == IntroState::disappear2)
	{
		textRenderer->SetTextColor(Color(1, 1, 1, 1 - time * 4));

		if (time >= 0.25f)
		{
			state = IntroState::nextWait;
			textRenderer->SetTextColor(Color(1, 1, 1, 0));
			time = 0;
		}
	}
	else if (state == IntroState::nextWait)
	{
		effect->ClearEffectInfo()
			->PushEffectInfo(new ColorMatrixEffectInfo(Color(1, 1, 1, 1 - time * 2)));

		if (time >= 0.5f)
		{
			RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}
	}
}