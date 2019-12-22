#include "stdafx.h"
#include "Engine.h"
#include "MapCreateScene.h"
#include "MapEditData.h"
#include "SceneData.h"

#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"

MapCreateScene::MapCreateScene()
{

}

MapCreateScene::~MapCreateScene()
{

}

Vec2L MapCreateScene::GetTilePos()
{
	Vec2F pos = RG2R_InputM->GetMouseWorldPos();
	pos += Vec2F(0.5f, 0.5f);
	pos = Vec2F(floor(pos.x), floor(pos.y));

	return Vec2L(pos.x, pos.y);
}

void MapCreateScene::OnStart()
{
	cursor = new Cursor;
	AttachObject(cursor);

	palette = new Palette;
	AttachObject(palette);

	sceneChangeManager = new SceneChangeManager2(this);
	AttachObject(sceneChangeManager);

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));

	if (SceneData::GetInstance()->inGameCode == 0)
	{
		tryb = new TryButtonM(true, this);
		reset = new ResetButtonM(true, this);
		menu = new MenuButtonM(true, this);
	}
	else
	{
		tryb = new TryButtonM(false, this);
		reset = new ResetButtonM(false, this);
		menu = new MenuButtonM(false, this);
	}
	AttachObject(tryb);
	AttachObject(reset);
	AttachObject(menu);

	auto w = MapEditData::GetInstance()->width;
	auto h = MapEditData::GetInstance()->height;

	if (w == 4 && h == 4)
		MapEditData::GetInstance()->zoom = 0.75f;
	else if (w == 5 && h == 5)
		MapEditData::GetInstance()->zoom = 0.6f;
	else if (w == 6 && h == 6)
		MapEditData::GetInstance()->zoom = 0.5f;
	else if (w == 7 && h == 7)
		MapEditData::GetInstance()->zoom = 0.45f;
	else if (w == 5 && h == 3)
		MapEditData::GetInstance()->zoom = 0.75f;
	else if (w == 6 && h == 4)
		MapEditData::GetInstance()->zoom = 0.6f;
	else if (w == 7 && h == 5)
		MapEditData::GetInstance()->zoom = 0.5f;
	else if (w == 8 && h == 6)
		MapEditData::GetInstance()->zoom = 0.45f;

	tiles = new Tiles(w, h);
	AttachObject(tiles);

	GetMainCamera()->SetZoom(MapEditData::GetInstance()->zoom, MapEditData::GetInstance()->zoom);
	if (MapEditData::GetInstance()->width % 2 == 0)
		GetMainCamera()->Translate(-0.5f, 0);
	if (MapEditData::GetInstance()->height % 2 == 0)
		GetMainCamera()->Translate(0, -0.5f);
}

void MapCreateScene::OnUpdate()
{

}

void MapCreateScene::Disappear(int code)
{
	if (!isFinish)
	{
		isFinish = true;

		if (code == 1) // 재시작
		{
			SceneData::GetInstance()->inGameCode = 1;
			tiles->Down();
			palette->Disappear();
			sceneChangeManager->Reset();
		}
		else if (code == 2) // 시도하기
		{
			SceneData::GetInstance()->inGameCode = 1;
			tiles->Down();
			palette->Disappear();
			//sceneChangeManager->Try();
		}
		else if (code == 3) // 스테이지 선택으로
		{
			SceneData::GetInstance()->inGameCode = 0;
			tryb->Disappear();
			reset->Disappear();
			menu->Disappear();
			palette->Disappear();
			tiles->Down();
			sceneChangeManager->Back();
		}
	}
}