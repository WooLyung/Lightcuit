#include "stdafx.h"
#include "GameInputManager.h"
#include "InGameScene.h"
#include "Engine.h"
#include "Battery.h"

GameInputManager::GameInputManager(InGameScene* scene)
{
	this->scene = scene;
}

GameInputManager::~GameInputManager()
{
}

void GameInputManager::OnUpdate()
{
	if (scene->playManager->gameState == GameState::CircuitDesign)
	{
		Input();
		GateMove();
		LineConnect();
	}
}

void GameInputManager::OnStart()
{
	colorSet = new ColorSet;
	AttachObject(colorSet);
}

void GameInputManager::LineConnect()
{
	Vec2L tilePos = scene->GetTilePos();

	if (inputState == InputState::LINE_START
		|| inputState == InputState::LINE_CONNECT)
	{
		if (!(tilePos.x >= -scene->mapSize.x / 2 && tilePos.x <= scene->mapSize.x / 2
			&& tilePos.y >= -scene->mapSize.y / 2 && tilePos.y <= scene->mapSize.y / 2))
		{
			LineCancel();
			return;
		}

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

						for (auto& iter : scene->objectManager->gates)
						{
							if (iter->tilePos == tilePos) // 게이트에 닿을 경우 연결 종료
							{
								canConnect = false;
							}
						}
						for (auto& iter : scene->objectManager->lines)
						{
							if (iter->tilePos == tilePos) // 기존에 있는 선과 겹칠 경우 연결 종료
							{
								canConnect = false;
							}
						}

						if (canConnect)
						{
							inputState = InputState::LINE_CONNECT;

							Line* newLine = new Line(tilePos.x, tilePos.y);
							newLine->preGate = myGate;
							scene->objectManager->connectingLine.push_back(newLine);
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
				Line* lastLine = scene->objectManager->connectingLine[scene->objectManager->connectingLine.size() - 1];

				if (tilePos.x != lastLine->tilePos.x || tilePos.y != lastLine->tilePos.y) // 이동했을 때
				{
					if ((abs(tilePos.x - lastLine->tilePos.x) == 1 && abs(tilePos.y - lastLine->tilePos.y) == 0)
						|| (abs(tilePos.x - lastLine->tilePos.x) == 0 && abs(tilePos.y - lastLine->tilePos.y) == 1))
						// 상하좌우 한칸만 이동했을 때
					{
						bool canConnect = true;
						bool isFinish = false;
						Gate* connectGate = nullptr;

						for (auto& iter : scene->objectManager->connectingLine)
						{
							if (iter->tilePos == tilePos) // 연결되고 있는 선과 겹칠 경우 연결 종료
							{
								canConnect = false;
							}
						}
						for (auto& iter : scene->objectManager->gates)
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
						}
						for (auto& iter : scene->objectManager->lines)
						{
							if (iter->tilePos == tilePos) // 기존에 있는 선과 겹칠 경우 연결 종료
							{
								canConnect = false;
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
								for (auto& iter : scene->objectManager->connectingLine)
								{
									scene->objectManager->lines.push_back(iter);
								}
								myGate->nextLine.push_back(scene->objectManager->connectingLine[0]);
								connectGate->preLine.push_back(lastLine);
								lastLine->nextGate = connectGate;
								scene->objectManager->SetSpriteOnFinish(lastLine, tilePos);

								scene->objectManager->connectingLine.clear();
								myGate->GetSpriteRenderer()->SetZ_index(0);
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
								newLine->preLine = lastLine;
								lastLine->nextLine = newLine;
								scene->objectManager->connectingLine.push_back(newLine);
								AttachObject(newLine);

								scene->objectManager->SetSpriteOnConnect(lastLine, newLine, tilePos);
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

void GameInputManager::LineUnconnect(Gate* gate)
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

	Gate* preGate = nullptr;
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
						preGate = line->preGate;
						break;
					}
				}
				break;
			}

			line = line->preLine;
		}
	}
	gate->preLine.clear();
	gate->nextLine.clear();

	vector<Line*> deleteLines;
	for (auto& iter : scene->objectManager->lines)
	{
		if (iter->GetState() == ObjectState::OBJ_DESTROY)
			deleteLines.push_back(iter);
	}
	for (auto& iter : deleteLines)
	{
		scene->objectManager->lines.remove(iter);
	}
}

void GameInputManager::LineCancel()
{
	for (auto& iter : scene->objectManager->connectingLine)
	{
		iter->Destroy();
	}

	scene->objectManager->connectingLine.clear();
	myGate->GetSpriteRenderer()->SetZ_index(0);
	myGate = nullptr;
	inputState = InputState::NONE;
}

void GameInputManager::GateMove()
{
	Vec2L tilePos = scene->GetTilePos();

	if (inputState == InputState::GATE_LIFT)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_STAY)
		{
			myGate->GetTransform()->SetPos(RG2R_InputM->GetMouseWorldPos());
		}
		else if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_EXIT)
		{
			if (!(tilePos.x >= -scene->mapSize.x / 2 && tilePos.x <= scene->mapSize.x / 2
				&& tilePos.y >= -scene->mapSize.y / 2 && tilePos.y <= scene->mapSize.y / 2))
			{
				myGate->SetPos(myGate->tilePos.x, myGate->tilePos.y);
				inputState = InputState::NONE;
				myGate->GetSpriteRenderer()->SetZ_index(0);
				myGate = nullptr;
				return;
			}

			Vec2L tilePos = scene->GetTilePos();
			Gate* targetGate = nullptr;
			Line* targetLine = nullptr;
			for (auto& iter : scene->objectManager->gates)
			{
				if (iter->tilePos.x == tilePos.x && iter->tilePos.y == tilePos.y)
				{
					targetGate = iter;
					break;
				}
			}
			for (auto& iter : scene->objectManager->lines)
			{
				if (iter->tilePos.x == tilePos.x && iter->tilePos.y == tilePos.y)
				{
					targetLine = iter;
					break;
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
			myGate->GetSpriteRenderer()->SetZ_index(0);
			myGate = nullptr;
		}
	}
}

void GameInputManager::Input()
{
	Vec2L tilePos = scene->GetTilePos();
	Gate* targetGate = nullptr;
	for (auto& iter : scene->objectManager->gates)
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

		for (auto& iter : scene->objectManager->lines)
		{
			if (iter->tilePos == tilePos)
			{
				targetLine = iter;
			}
		}

		if (targetLine != nullptr)
		{
			vector<Line*> deleteLines;

			while (true)
			{
				if (targetLine->preLine == nullptr)
					break;

				targetLine = targetLine->preLine;
			}
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
				deleteLines.push_back(targetLine);

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

			for (auto& iter : deleteLines)
			{
				scene->objectManager->lines.remove(iter);
			}
		}
	}
#pragma endregion
#pragma region 좌클릭 중심 (이동)
	if (targetGate != nullptr)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER
			&& inputState == InputState::NONE)
		{
			Vec2F mousePos = RG2R_InputM->GetMouseWorldPos();
			if (mousePos.x >= tilePos.x - 0.25f
				&& mousePos.y >= tilePos.y - 0.25f
				&& mousePos.x <= tilePos.x + 0.25f
				&& mousePos.y <= tilePos.y + 0.25f)
			{
				inputState = InputState::GATE_LIFT;
				myGate = targetGate;
				myGate->GetSpriteRenderer()->SetZ_index(2);
				LineUnconnect(targetGate);
			}
		}
	}
#pragma endregion
#pragma region 좌클릭 가장자리 (연결)
	if (targetGate != nullptr)
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER
			&& inputState == InputState::NONE)
		{
			Vec2F mousePos = RG2R_InputM->GetMouseWorldPos();
			if (!(mousePos.x >= tilePos.x - 0.25f
				&& mousePos.y >= tilePos.y - 0.25f
				&& mousePos.x <= tilePos.x + 0.25f
				&& mousePos.y <= tilePos.y + 0.25f))
			{
				inputState = InputState::LINE_START;
				myGate = targetGate;
			}
		}
	}
#pragma endregion
#pragma region 우클릭 (색 변경)
	if (targetGate != nullptr
		&& targetGate->GetID() == typeid(Battery))
	{
		if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_ENTER
			&& inputState == InputState::NONE)
		{
			inputState = InputState::COLOR_CHANGE;
			colorSet->SetIsEnable(true);
			colorSet->SetPos(tilePos.x, tilePos.y);
			myGate = targetGate;
		}
	}
	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_RBUTTON) == KeyState::KEYSTATE_EXIT
		&& inputState == InputState::COLOR_CHANGE)
	{
		inputState = InputState::NONE;
		colorSet->SetIsEnable(false);
		if (colorSet->GetColor() != Color8(1, 1, 1))
			myGate->SetColor(colorSet->GetColor());
		myGate = nullptr;
	}
#pragma endregion
}