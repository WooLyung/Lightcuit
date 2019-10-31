#include "stdafx.h"
#include "InGameScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "AddGate.h"
#include "Light1.h"
#include "Light2.h"
#include "Battery.h"
#include "Gate.h"
#include "Line.h"
#include "DivisionGate.h"
#include "SubGate.h"
#include "ReverseGate.h"
#include "ColorSet.h"
#include "ObjectManager.h"
#include "GameInputManager.h"

InGameScene::InGameScene()
{
	GetMainCamera()->SetZoom(0.5f, 0.5f);
}

InGameScene::~InGameScene()
{
}

void InGameScene::OnStart()
{
	objectManager = new ObjectManager(this);
	gameInputManager = new GameInputManager(this);
	playManager = new PlayManager(this);
	AttachObject(objectManager);
	AttachObject(gameInputManager);
	AttachObject(playManager);

	auto obj = CreateObject()
		->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/check.png")
		->GetOwner()
		->AttachComponent<Transform>()
		->SetAnchor(448, 448)
		->GetOwner();
	obj->GetComponent<SpriteRenderer>()
		->SetZ_index(-1);

	PushGate(new Battery(1, 0));
	PushGate(new Battery(2, 0));
	PushGate(new Battery(3, 0));
	PushGate(new Battery(-5, 0));

	PushGate(new DivisionGate(4, 0));
	PushGate(new DivisionGate(1, 2));
	PushGate(new DivisionGate(-1, 2));
	PushGate(new DivisionGate(-2, 2));
	PushGate(new AddGate(0, 2));
	PushGate(new AddGate(1, 3));
	PushGate(new AddGate(2, 3));
	PushGate(new SubGate(1, 1));

	PushGate(new ReverseGate(0, 3));
	PushGate(new ReverseGate(3, 3));

	PushGate(new Light1(0, 4));
	PushGate(new Light1(1, 4));
	PushGate(new Light2(2, 4));

	// 둘 들어와서 더한거의 반전 하나로
	// 하나 들어와서 하나는 그대로, 하나는 반전
	// 하나 들어와서 둘 다 반전
	// 하나 들어와서 특정 색 더하고 하나로
	// 하나 들어와서 특정 색 빼고 하나로
}

void InGameScene::OnUpdate()
{
}

Vec2L InGameScene::GetTilePos()
{
	Vec2F pos = RG2R_InputM->GetMouseWorldPos();
	pos += Vec2F(0.5f, 0.5f);
	pos = Vec2F(floor(pos.x), floor(pos.y));

	return Vec2L(pos.x, pos.y);
}

void InGameScene::PushGate(Gate* gate)
{
	objectManager->PushGate(gate);
}