#include "stdafx.h"
#include "PlayManager.h"
#include "Engine.h"
#include "CommandList.h"
#include "StageClearObj.h"

#include "Battery.h"
#include "AddGate.h"
#include "DivisionGate.h"
#include "ReverseGate.h"
#include "SubGate.h"
#include "Light2.h"

#include <stack>

PlayManager::PlayManager(InGameScene* scene)
{
	this->scene = scene;
}

PlayManager::~PlayManager()
{
}

void PlayManager::OnStart()
{
	gameNotClear = new CommandList;
	gameNotClear->PushCommand([=]() {
		for (auto& iter : scene->objectManager->gates)
		{
			if (iter->GetID() != typeid(Battery))
			{
				iter->SetColor(Color(1, 1, 1, 1));
			}
		}
		for (auto& iter : scene->objectManager->lines)
		{
			iter->SetColor(Color(1, 1, 1, 1));
		}
		}, 1.5f)
		->PushCommand([=]() {
			gameState = GameState::CircuitDesign;
			}, 0.5f);
		commandLists.push_back(gameNotClear);

	clearEffect = new CommandList;
	clearEffect->PushCommand([=]() {
		for (auto& iter : scene->objectManager->gates)
		{
			iter->SetColor(clearEffectColor);
		}
		for (auto& iter : scene->objectManager->lines)
		{
			iter->SetColor(clearEffectColor);
		}

		if (clearEffectColor == Color8(1, 0, 0))
			clearEffectColor = Color8(0, 1, 0);
		else if (clearEffectColor == Color8(0, 1, 0))
			clearEffectColor = Color8(0, 0, 1);
		else if (clearEffectColor == Color8(0, 0, 1))
			clearEffectColor = Color8(1, 0, 0);

		}, 0.6f);
	clearEffect->SetIsLoop(true);
	commandLists.push_back(clearEffect);

	tryPlay = new CommandList;
	tryPlay->PushCommand([=]() {
		if (!term)
		{
			if (sortedNodes[playIndex]->type == 1) // 라인
			{
				Color8 color;

				if (sortedNodes[playIndex]->line->preGate != nullptr)
					color = sortedNodes[playIndex]->line->preGate->GetColor();
				else
					color = sortedNodes[playIndex]->line->preLine->GetColor();

				sortedNodes[playIndex]->line->SetColor(color);
			}
			else // 게이트
			{
				Color8 color;

				if (sortedNodes[playIndex]->gate->GetID() == typeid(AddGate)
					|| sortedNodes[playIndex]->gate->GetID() == typeid(Light))
				{
					for (auto line : sortedNodes[playIndex]->gate->preLine)
					{
						color = (Color8)(color + line->GetColor());
					}
					sortedNodes[playIndex]->gate->SetColor(color);
				}
				else if (sortedNodes[playIndex]->gate->GetID() == typeid(DivisionGate))
				{
					color = sortedNodes[playIndex]->gate->preLine[0]->GetColor();
					sortedNodes[playIndex]->gate->SetColor(color);
				}
				else if (sortedNodes[playIndex]->gate->GetID() == typeid(ReverseGate))
				{
					color = !sortedNodes[playIndex]->gate->preLine[0]->GetColor();
					sortedNodes[playIndex]->gate->SetColor(color);
				}
				else if (sortedNodes[playIndex]->gate->GetID() == typeid(SubGate))
				{
					Color8 color1, color2;

					if (sortedNodes[playIndex]->gate->GetDir() == Dir::RIGHT
						&& sortedNodes[playIndex]->gate->preLine[0]->tilePos.x < sortedNodes[playIndex]->gate->tilePos.x
						|| sortedNodes[playIndex]->gate->GetDir() == Dir::LEFT
						&& sortedNodes[playIndex]->gate->preLine[0]->tilePos.x > sortedNodes[playIndex]->gate->tilePos.x
						|| sortedNodes[playIndex]->gate->GetDir() == Dir::UP
						&& sortedNodes[playIndex]->gate->preLine[0]->tilePos.y < sortedNodes[playIndex]->gate->tilePos.y
						|| sortedNodes[playIndex]->gate->GetDir() == Dir::DOWN
						&& sortedNodes[playIndex]->gate->preLine[0]->tilePos.y > sortedNodes[playIndex]->gate->tilePos.y)
					{
						color1 = sortedNodes[playIndex]->gate->preLine[0]->GetColor();
						color2 = sortedNodes[playIndex]->gate->preLine[1]->GetColor();
					}
					else
					{
						color1 = sortedNodes[playIndex]->gate->preLine[1]->GetColor();
						color2 = sortedNodes[playIndex]->gate->preLine[0]->GetColor();
					}

					color = color1 - color2;
					sortedNodes[playIndex]->gate->SetColor(color);
				}
			}
			this->playIndex++;

			if (playIndex >= sortedNodes.size())
			{
				tryPlay->Stop();
				Result();
			}
			else if (sortedNodes[playIndex]->type == 0)
			{
				term = 5;
			}
		}
		else
		{
			term--;
		}}, 0.03f);
	tryPlay->SetIsLoop(true);
	commandLists.push_back(tryPlay);
}

int PlayManager::CheckClear()
{
	std::map<Object*, Node*> map;
	std::vector<Node*> nodes;
	std::stack<Node*> nodeStack;

	for (auto& iter : sortedNodes)
	{
		delete iter;
	}
	sortedNodes.clear();

	for (auto& iter : scene->objectManager->gates)
	{
		Node* node = new Node;
		node->gate = iter;
		node->type = 0;
		map.insert(std::pair<Object*, Node*>(iter, node));
		nodes.push_back(node);
	}
	for (auto& iter : scene->objectManager->lines)
	{
		Node* node = new Node;
		node->line = iter;
		node->type = 1;
		map.insert(std::pair<Object*, Node*>(iter, node));
		nodes.push_back(node);
	}

	for (auto& node : nodes)
	{
		if (node->type == 0) // 게이트
		{
			if (node->gate->output.size() != node->gate->nextLine.size()
				|| node->gate->input.size() != node->gate->preLine.size())
			{
				return 1; // 모든 게이트들이 연결되지 않음
			}

			for (auto iter : node->gate->nextLine)
			{
				node->next.push_back(map[iter]);
			}

			if (node->gate->GetID() == typeid(Battery))
			{
				nodeStack.push(node);
			}
		}
		else // 라인
		{
			if (node->line->nextLine != nullptr)
				node->next.push_back(map[node->line->nextLine]);
			else
				node->next.push_back(map[node->line->nextGate]);
		}

		for (auto iter : node->next)
			iter->inDegree++;
	}

	while (nodeStack.size() > 0)
	{
		Node* node = nodeStack.top();
		nodeStack.pop();
		sortedNodes.push_back(node);

		for (auto iter : node->next)
		{
			iter->inDegree--;

			if (iter->inDegree == 0)
			{
				nodeStack.push(iter);
			}
		}
	}

	if (sortedNodes.size() != nodes.size())
		return 2;

	return 0;
}

void PlayManager::Play()
{
	playIndex = 0;
	gameState = GameState::Try;
	tryPlay->Start();
}

void PlayManager::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_F) == KeyState::KEYSTATE_ENTER)
	{
		if (!CheckClear())
			Play();
	}
}

void PlayManager::Result()
{
	bool isClear = true;
	for (auto& iter : scene->objectManager->gates)
	{
		if (iter->GetID() == typeid(Light) && iter->GetColor() != Color8(1, 1, 1))
		{
			isClear = false;
		}
	}

	if (isClear)
	{
		//clearEffect->Start();
		//AttachObject(new StageClearObj);
		gameState = GameState::Clear;
	}
	else
	{
		gameNotClear->Start();
	}
}