#include "stdafx.h"
#include "InGameScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "AddGate.h"
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
	AttachObject(objectManager);
	AttachObject(gameInputManager);

	auto obj = CreateObject()
		->AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/check.png")
		->GetOwner()
		->AttachComponent<Transform>()
		->SetAnchor(448, 448)
		->GetOwner();
	obj->GetComponent<SpriteRenderer>()
		->SetZ_index(-1);

	PushGate(new AddGate(0, 0));
	PushGate(new DivisionGate(0, 1));
	PushGate(new SubGate(1, 1));
	PushGate(new Light2(-2, -2));
	PushGate(new ReverseGate(-2, 1));
	PushGate(new Battery(3, 3));
	PushGate(new Battery(2, 1));
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