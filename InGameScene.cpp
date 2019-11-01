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
#include "StageData.h"
#include <fstream>

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
		->SetAnchor(1402 * 0.5f, 896 * 0.5f)
		->GetOwner();
	obj->GetComponent<SpriteRenderer>()
		->SetZ_index(-1);

	Init();
}

void InGameScene::OnUpdate()
{
}

void InGameScene::Init()
{
	std::string path = "Resources/Maps/";
	path += std::to_string(StageData::GetInstance()->chapter) + "Chapter/";
	path += std::to_string(StageData::GetInstance()->stage) + "stage.txt";

	std::string data;
	std::ifstream in(path);
	while (getline(in, data)) {
		size_t start_pos = 0;
		while ((start_pos = data.find(" ", start_pos)) != std::string::npos)
		{
			data.replace(start_pos, string(" ").length(), "");
			start_pos += string("").length();
		}

		string splitedString, key, value;
		std::map<string, string> gateData;
		size_t begin = 0, end = 1;

		while (true)
		{
			end++;
			if (data[end] == ',' || end == data.size())
			{
				splitedString = data.substr(begin, end - begin);

				key = splitedString.substr(0, splitedString.find(":"));
				value = splitedString.substr(splitedString.find(":") + 1, splitedString.size());

				gateData.insert(std::pair<string, string>(key, value));

				begin = ++end;
			}
			if (end >= data.size())
				break;
		}

		CreateGate(gateData);
	}
	in.close();
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

void InGameScene::CreateGate(std::map<string, string> data)
{
	Dir dir = Dir::RIGHT;
	if (data.find("dir") != data.end())
	{
		if (data["dir"] == "right")
			dir = Dir::RIGHT;
		else if (data["dir"] == "left")
			dir = Dir::LEFT;
		else if (data["dir"] == "up")
			dir = Dir::UP;
		else if (data["dir"] == "down")
			dir = Dir::DOWN;
	}

	int x = std::stoi(data["x"]);
	int y = std::stoi(data["y"]);

	if (data["type"] == "battery")
	{
		Color8 color = Color8(1, 0, 0);
		if (data.find("color") != data.end())
		{
			if (data["color"] == "red")
				color = Color8(1, 0, 0);
			else if (data["color"] == "green")
				color = Color8(0, 1, 0);
			else if (data["color"] == "blue")
				color = Color8(0, 0, 1);
		}

		PushGate(new Battery(x, y, dir, color));
	}
	else if (data["type"] == "add_gate")
	{
		PushGate(new AddGate(x, y, dir));
	}
	else if (data["type"] == "division_gate")
	{
		PushGate(new DivisionGate(x, y, dir));
	}
	else if (data["type"] == "sub_gate")
	{
		PushGate(new SubGate(x, y, dir));
	}
	else if (data["type"] == "light1")
	{
		PushGate(new Light1(x, y, dir));
	}
	else if (data["type"] == "light2")
	{
		PushGate(new Light2(x, y, dir));
	}
	else if (data["type"] == "reverse_gate")
	{
		PushGate(new ReverseGate(x, y, dir));
	}
}