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
#include "ObjectManager.h"
#include "GameInputManager.h"
#include "StageData.h"
#include "SceneData.h"
#include <fstream>

#include "Pen1.h"
#include "Pen2.h"
#include "Pen3.h"
#include "Ruler1.h"
#include "Ruler2.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::OnStart()
{
	objectManager = new ObjectManager(this);
	gameInputManager = new GameInputManager(this);
	playManager = new PlayManager(this);
	sceneChangeManager = new SceneChangeManager(this);

	AttachObject(objectManager);
	AttachObject(gameInputManager);
	AttachObject(playManager);
	AttachObject(sceneChangeManager);

	AttachObject(new Pen1(false));
	AttachObject(new Pen2(false));
	AttachObject(new Pen3(false));
	AttachObject(new Ruler1(false));
	AttachObject(new Ruler2(false));

	if (SceneData::GetInstance()->inGameCode == 0)
	{
		playButton = new PlayButton(true, this);
		resetButton = new ResetButton(true, this);
		menuButton = new MenuButton(true, this);
	}
	else
	{
		playButton = new PlayButton(false, this);
		resetButton = new ResetButton(false, this);
		menuButton = new MenuButton(false, this);
	}
	popup = new Popup;
	postit = new PostIt(true);

	AttachObject(popup);
	AttachObject(postit);
	AttachObject(playButton);
	AttachObject(resetButton);
	AttachObject(menuButton);

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

		if (gateData.find("type") == gateData.end())
		{
			mapSize.x = std::stoi(gateData["x"]);
			mapSize.y = std::stoi(gateData["y"]);
			GetMainCamera()->SetZoom(std::stof(gateData["zoom"]), std::stof(gateData["zoom"]));

			string text = gateData["text"];
			size_t start_pos = 0;
			while ((start_pos = text.find("_", start_pos)) != std::string::npos)
			{
				text.replace(start_pos, string("_").length(), " ");
				start_pos += string(" ").length();
			}
			start_pos = 0;
			while ((start_pos = text.find("\\", start_pos)) != std::string::npos)
			{
				text.replace(start_pos, string("\\").length(), "\n");
				start_pos += string("\n").length();
			}

			postit->GetTextRenderer()->SetText(text);

			tiles = new Tiles(mapSize.x, mapSize.y);
			AttachObject(tiles);
		}
		else
		{
			CreateGate(gateData);
		}
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
	Gate* gate = nullptr;

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

		gate = new Battery(x, y, dir, color);
		PushGate(gate);
	}
	else if (data["type"] == "add_gate")
	{
		gate = new AddGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "division_gate")
	{
		gate = new DivisionGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "sub_gate")
	{
		gate = new SubGate(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "light1")
	{
		gate = new Light1(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "light2")
	{
		gate = new Light2(x, y, dir);
		PushGate(gate);
	}
	else if (data["type"] == "reverse_gate")
	{
		gate = new ReverseGate(x, y, dir);
		PushGate(gate);
	}

	if (gate != nullptr)
	{
		gate->ChangeParent(tiles);
	}
}

void InGameScene::PopMsg(int code)
{
	popup->Pop(code);
}

void InGameScene::Disappear(int code)
{
	if (!isFinish)
	{
		isFinish = true;

		if (code == 1) // 재시작
		{
			SceneData::GetInstance()->inGameCode = 1;
			postit->Disappear();
			tiles->Down();
			sceneChangeManager->Reset();
		}
		else if (code == 2) // 다른 스테이지
		{
			SceneData::GetInstance()->inGameCode = 1;
			postit->Disappear();
			tiles->Down();
			sceneChangeManager->Diff();
		}
		else if (code == 3) // 스테이지 선택으로
		{
			SceneData::GetInstance()->inGameCode = 0;
			postit->Disappear();
			playButton->Disappear();
			resetButton->Disappear();
			menuButton->Disappear();
			tiles->Down();
			sceneChangeManager->Back();
		}
	}
}