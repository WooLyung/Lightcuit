#include "stdafx.h"
#include "InGameScene.h"
#include "SpriteRenderer.h"
#include "Transform.h"
#include "Engine.h"
#include "AddGate.h"
#include "Battery.h"
#include "Gate.h"
#include "Line.h"
#include "DivisionGate.h"

Dir RotatedDir(Dir dir)
{
	switch (dir)
	{
	case (Dir::LEFT):
		return Dir::UP;
	case (Dir::DOWN):
		return Dir::LEFT;
	case (Dir::RIGHT):
		return Dir::DOWN;
	default:
		return Dir::RIGHT;
	}
}

InGameScene::InGameScene()
{
	GetMainCamera()->SetZoom(0.5f, 0.5f);
}

InGameScene::~InGameScene()
{
}

void InGameScene::OnStart()
{
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
	PushGate(new Battery(3, 3));
	PushGate(new Battery(2, 1));
	PushGate(new DivisionGate(0, 1));
}

void InGameScene::OnUpdate()
{
	Input();
	GateMove();
	LineConnect();
}

void InGameScene::LineConnect()
{
	Vec2L tilePos = GetTilePos();

	if (inputState == InputState::LINE_START
		|| inputState == InputState::LINE_CONNECT)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY) // 좌클릭 유지
		{
			if (inputState == InputState::LINE_START) // 시작
			{
				if (tilePos.x != myGate->tilePos.x || tilePos.y != myGate->tilePos.y) // 이동했을 때
				{
					if ((abs(tilePos.x - myGate->tilePos.x) == 1 && abs(tilePos.y - myGate->tilePos.y) == 0)
						|| (abs(tilePos.x - myGate->tilePos.x) == 0 && abs(tilePos.y - myGate->tilePos.y) == 1))
						// 상하좌우 한칸만 이동했을 때
					{
						bool canConnect = false;
						Dir dir = LEFT;

						if (tilePos.x > myGate->tilePos.x)
							dir = RIGHT;
						else if (tilePos.x < myGate->tilePos.x)
							dir = LEFT;
						else if (tilePos.y > myGate->tilePos.y)
							dir = UP;
						else if (tilePos.y < myGate->tilePos.y)
							dir = DOWN;

						for (int i = 0; i < myGate->output.size(); i++)
							if (myGate->output[i] == dir)
								canConnect = true;

						for (auto& iter : gates)
						{
							if (iter->tilePos == tilePos) // 게이트에 닿을 경우 연결 종료
							{
								canConnect = false;
							}
							else
							{
								for (auto& iter2 : iter->connectedLine)
								{
									if (iter2->tilePos == tilePos) // 기존에 있는 선과 겹칠 경우 연결 종료
									{
										canConnect = false;
									}
								}
							}
						}

						if (canConnect)
						{
							inputState = InputState::LINE_CONNECT;

							Line* newLine = new Line(tilePos.x, tilePos.y);
							newLine->preGate = myGate;
							connectingLine.push_back(newLine);
							AttachObject(newLine);

							if (tilePos.x > myGate->tilePos.x)
							{
								newLine->GetTransform()->SetRot(0);
							}
							else if (tilePos.x < myGate->tilePos.x)
							{
								newLine->GetTransform()->SetRot(180);
							}
							else if (tilePos.y > myGate->tilePos.y)
							{
								newLine->GetTransform()->SetRot(270);
							}
							else if (tilePos.y < myGate->tilePos.y)
							{
								newLine->GetTransform()->SetRot(90);
							}

							newLine->dir = dir;
						}
						else
						{
							LineCancel();
						}
					}
					else
					{
						LineCancel();
					}
				}
			}
			else if (inputState == InputState::LINE_CONNECT) // 연결중
			{
				Line* lastLine = connectingLine[connectingLine.size() - 1];

				if (tilePos.x != lastLine->tilePos.x || tilePos.y != lastLine->tilePos.y) // 이동했을 때
				{
					if ((abs(tilePos.x - lastLine->tilePos.x) == 1 && abs(tilePos.y - lastLine->tilePos.y) == 0)
						|| (abs(tilePos.x - lastLine->tilePos.x) == 0 && abs(tilePos.y - lastLine->tilePos.y) == 1))
						// 상하좌우 한칸만 이동했을 때
					{
						bool canConnect = true;
						bool isFinish = false;
						Gate* connectGate = nullptr;

						for (auto& iter : connectingLine)
						{
							if (iter->tilePos == tilePos) // 연결되고 있는 선과 겹칠 경우 연결 종료
							{
								canConnect = false;
							}
						}
						for (auto& iter : gates)
						{
							if (iter->tilePos == tilePos) // 게이트에 닿을 경우 연결 완료
							{
								if (iter == myGate) // 같은 게이트면 연결 취소
								{
									canConnect = false;
								}
								else // 다른 게이트면 연결 완료
								{
									isFinish = true;
									connectGate = iter;
								}
							}
							else
							{
								for (auto& iter2 : iter->connectedLine)
								{
									if (iter2->tilePos == tilePos) // 기존에 있는 선과 겹칠 경우 연결 종료
									{
										canConnect = false;
									}
								}
							}
						}

						Dir dir = LEFT;
						if (tilePos.x > lastLine->tilePos.x)
							dir = LEFT;
						else if (tilePos.x < lastLine->tilePos.x)
							dir = RIGHT;
						else if (tilePos.y > lastLine->tilePos.y)
							dir = DOWN;
						else if (tilePos.y < lastLine->tilePos.y)
							dir = UP;

						if (isFinish)
						{
							isFinish = false;

							for (int i = 0; i < connectGate->input.size(); i++)
							{
								if (connectGate->input[i] == dir)
								{
									isFinish = true;
									break;
								}
							}

							if (isFinish)
							{
								for (auto& iter : connectingLine)
								{
									connectGate->connectedLine.push_back(iter);
								}
								myGate->nextLine.push_back(connectingLine[0]);
								connectGate->preLine.push_back(lastLine);
								lastLine->nextGate = connectGate;
								SetSpriteOnFinish(lastLine, tilePos);

								connectingLine.clear();
								myGate = nullptr;
								inputState = InputState::NONE;
							}
							else
							{
								LineCancel();
							}
						}
						else
						{
							if (canConnect)
							{
								Line* newLine = new Line(tilePos.x, tilePos.y);
								newLine->preLine = connectingLine[connectingLine.size() - 1];
								connectingLine[connectingLine.size() - 1]->nextLine = newLine;
								connectingLine.push_back(newLine);
								AttachObject(newLine);

								SetSpriteOnConnect(lastLine, newLine, tilePos);
							}
							else
							{
								LineCancel();
							}
						}
					}
					else // 여러칸을 이동하거나 대각선으로 이동했을 때
					{
						LineCancel();
					}
				}
			}
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT) // 좌클릭 종료
		{
			LineCancel();
		}
	}
}

void InGameScene::SetSpriteOnFinish(Line* line, Vec2L tilePos)
{
	Transform* lineTrans = line->GetTransform();
	SpriteRenderer* lineRen = line->GetSpriteRenderer();

	if (line->dir == RIGHT)
	{
		if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(90);
		}
		else if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(0);
		}
	}
	else if (line->dir == LEFT)
	{
		if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(180);
		}
		else if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(270);
		}
	}
	else if (line->dir == UP)
	{
		if (tilePos.y > line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(270);
		}
		else if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(0);
		}
	}
	else if (line->dir == DOWN)
	{
		if (tilePos.y < line->tilePos.y)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line2.png");
		}
		else if (tilePos.x > line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(180);
		}
		else if (tilePos.x < line->tilePos.x)
		{
			lineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lineTrans->SetRot(90);
		}
	}
}

void InGameScene::SetSpriteOnConnect(Line* lastLine, Line* newLine, Vec2L tilePos)
{
	Transform* newLineTrans = newLine->GetTransform();
	Transform* lastLineTrans = lastLine->GetTransform();
	SpriteRenderer* lastLineRen = lastLine->GetSpriteRenderer();

	if (lastLine->dir == RIGHT)
	{
		if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(90);
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(0);
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
	}
	else if (lastLine->dir == LEFT)
	{
		if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
		else if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(180);
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(270);
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
	}
	else if (lastLine->dir == UP)
	{
		if (tilePos.y > lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(270);
			newLine->dir = UP;
		}
		else if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(270);
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(0);
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
	}
	else if (lastLine->dir == DOWN)
	{
		if (tilePos.y < lastLine->tilePos.y)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line2.png");
			newLineTrans->SetRot(90);
			newLine->dir = DOWN;
		}
		else if (tilePos.x > lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(180);
			newLineTrans->SetRot(0);
			newLine->dir = RIGHT;
		}
		else if (tilePos.x < lastLine->tilePos.x)
		{
			lastLineRen->SetTexture("Resources/Sprites/Lines/line3.png");
			lastLineTrans->SetRot(90);
			newLineTrans->SetRot(180);
			newLine->dir = LEFT;
		}
	}
}

void InGameScene::LineUnconnect(Gate* gate)
{
	for (auto iter = gate->nextLine.begin(); iter != gate->nextLine.end(); iter++)
	{
		Line* line = *iter;

		while (true)
		{
			line->Destroy();

			if (line->nextGate != nullptr)
			{
				for (auto iter2 = line->nextGate->preLine.begin(); iter2 != line->nextGate->preLine.end(); iter2++)
				{
					if (*iter2 == line)
					{
						line->nextGate->preLine.erase(iter2);
						break;
					}
				}
				break;
			}

			line = line->nextLine;
		}
	}
	gate->nextLine.clear();

	for (auto iter = gate->preLine.begin(); iter != gate->preLine.end(); iter++)
	{
		Line* line = *iter;

		while (true)
		{
			line->Destroy();

			if (line->preGate != nullptr)
			{
				for (auto iter2 = line->preGate->nextLine.begin(); iter2 != line->preGate->nextLine.end(); iter2++)
				{
					if (*iter2 == line)
					{
						line->preGate->nextLine.erase(iter2);
						break;
					}
				}
				break;
			}

			line = line->preLine;
		}
	}
	gate->preLine.clear();

	gate->connectedLine.clear();
}

void InGameScene::LineCancel()
{
	for (auto& iter : connectingLine)
	{
		iter->Destroy();
	}

	connectingLine.clear();
	myGate = nullptr;
	inputState = InputState::NONE;
}

void InGameScene::GateMove()
{
	if (inputState == InputState::GATE_LIFT)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_MBUTTON) == KeyState::KEYSTATE_STAY)
		{
			myGate->GetTransform()->SetPos(RG2R_InputM->GetMouseWorldPos());
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_MBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			Vec2L tilePos = GetTilePos();
			Gate* targetGate = nullptr;
			Line* targetLine = nullptr;
			for (auto& iter : gates)
			{
				if (iter->tilePos.x == tilePos.x && iter->tilePos.y == tilePos.y)
				{
					targetGate = iter;
					break;
				}
				else
				{
					for (auto& iter2 : iter->connectedLine)
					{
						if (iter2->tilePos.x == tilePos.x && iter2->tilePos.y == tilePos.y)
						{
							targetLine = iter2;
							break;
						}
					}
				}
			}

			if (targetGate == nullptr && targetLine == nullptr) // 옮길 자리에 게이트가 없을 경우
			{
				myGate->SetPos(tilePos.x, tilePos.y);
			}
			else if (myGate->tilePos == tilePos) // 옮길 자리가 원래 위치
			{
				myGate->SetPos(myGate->tilePos.x, myGate->tilePos.y);
			}
			else // 옮길 자리에 게이트 혹은 라인이 있을 경우
			{
				myGate->SetPos(myGate->tilePos.x, myGate->tilePos.y);
			}

			inputState = InputState::NONE;
			myGate = nullptr;
		}
	}
}

void InGameScene::Input()
{
	Vec2L tilePos = GetTilePos();
	Gate* targetGate = nullptr;
	for (auto& iter : gates)
	{
		if (iter->tilePos.x == tilePos.x && iter->tilePos.y == tilePos.y)
		{
			targetGate = iter;
		}
	}

#pragma region R키 (회전)
	if (targetGate != nullptr)
	{
		if (targetGate != nullptr)
		{
			if (RG2R_InputM->GetKeyState(KeyCode::KEY_R) == KeyState::KEYSTATE_ENTER
				&& inputState == InputState::NONE)
			{
				targetGate->SetDir(RotatedDir(targetGate->GetDir()));
				for (int i = 0; i < targetGate->input.size(); i++)
					targetGate->input[i] = RotatedDir(targetGate->input[i]);
				for (int i = 0; i < targetGate->output.size(); i++)
					targetGate->output[i] = RotatedDir(targetGate->output[i]);

				LineUnconnect(targetGate);
			}
		}
	}
#pragma endregion
#pragma region E키 (연결된 선 삭제)
	if (targetGate != nullptr)
	{
		if (targetGate != nullptr)
		{
			if (RG2R_InputM->GetKeyState(KeyCode::KEY_E) == KeyState::KEYSTATE_ENTER
				&& inputState == InputState::NONE)
			{
				LineUnconnect(targetGate);
			}
		}
	}
	else if (RG2R_InputM->GetKeyState(KeyCode::KEY_E) == KeyState::KEYSTATE_ENTER
		&& inputState == InputState::NONE)
	{
		Line* targetLine = nullptr;

		for (auto& iter : gates)
		{
			for (auto& iter2 : iter->connectedLine)
			{
				if (iter2->tilePos == tilePos)
				{
					targetLine = iter2;
				}
			}
		}

		if (targetLine != nullptr)
		{
			while (true)
			{
				if (targetLine->preLine == nullptr)
					break;

				targetLine = targetLine->preLine;
			}
			targetLine->preGate->connectedLine.clear();
			for (auto iter = targetLine->preGate->nextLine.begin(); iter != targetLine->preGate->nextLine.end(); iter++)
			{
				if (*iter == targetLine)
				{
					targetLine->preGate->nextLine.erase(iter);
					break;
				}
			}

			while (true)
			{
				targetLine->Destroy();

				if (targetLine->nextGate != nullptr)
				{
					for (auto iter = targetLine->nextGate->preLine.begin(); iter != targetLine->nextGate->preLine.end(); iter++)
					{
						if (*iter == targetLine)
						{
							targetLine->nextGate->preLine.erase(iter);
							break;
						}
					}
					break;
				}

				targetLine = targetLine->nextLine;
			}
		}
	}
#pragma endregion
#pragma region 휠 클릭 (이동)
	if (targetGate != nullptr)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_MBUTTON) == KeyState::KEYSTATE_ENTER
			&& inputState == InputState::NONE)
		{
			inputState = InputState::GATE_LIFT;
			myGate = targetGate;
			LineUnconnect(targetGate);
		}
	}
#pragma endregion
#pragma region 좌클릭 (연결)
	if (targetGate != nullptr)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER
			&& inputState == InputState::NONE)
		{
			inputState = InputState::LINE_START;
			myGate = targetGate;
		}
	}
#pragma endregion
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
	AttachObject(gate);
	gates.push_back(gate);
}