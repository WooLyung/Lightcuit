#include "stdafx.h"
#include "MapEditCreate.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"
#include "PlayerData.h"

MapEditCreate::MapEditCreate(MapEditorScene* scene)
{
	this->scene = scene;
}

MapEditCreate::~MapEditCreate()
{
}

void MapEditCreate::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/MapEditor/mapeditor_create.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	spriteRenderer->SetZ_index(-2);
	transform = GetComponent<Transform>()
		->SetScale(0.8f, 0.8f)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.5f;
		transform->SetPos((1 - pow(animTime - 1, 2)) * 1 * Vec2F(-6.5f, 0));

		if (animTime >= 1)
		{
			transform->SetPos(Vec2F(-6.5f, 0));
			animTime = 0;
			appearAnim->Stop();
			state = StageState::wait2;
		}
		}, 0);
	appearAnim->SetIsLoop(true);

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime() * 2.f;
		transform->SetPos((pow(animTime - 1, 2)) * 1 * Vec2F(-6.5f, 0));

		if (animTime >= 1)
		{
			transform->SetPos(0, 0);
			animTime = 0;
			disappearAnim->Stop();
			state = StageState::disappear;
			spriteRenderer->SetIsEnable(false);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);
}

void MapEditCreate::OnUpdate()
{
	if (MapEditCreate::state == MapEditCreate::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		state = MapEditCreate::wait;
		animTime = 0;
		appearAnim->Start();
	}
}

Transform* MapEditCreate::GetTransform()
{
	return transform;
}

SpriteRenderer* MapEditCreate::GetSpriteRenderer()
{
	return spriteRenderer;
}

void MapEditCreate::Disappear()
{
	appearAnim->Stop();
	disappearAnim->Start();
}