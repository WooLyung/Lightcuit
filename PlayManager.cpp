#include "stdafx.h"
#include "PlayManager.h"
#include "Engine.h"
#include "CommandList.h"

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
	tryPlay = new CommandList;
	tryPlay->PushCommand([=]() {
		if (sortedNodes[playIndex]->type == 1) // ����
		{
			Color8 color;

			if (sortedNodes[playIndex]->line->preGate != nullptr)
				color = sortedNodes[playIndex]->line->preGate->GetColor();
			else
				color = sortedNodes[playIndex]->line->preLine->GetColor();

			sortedNodes[playIndex]->line->SetColor(color);
		}
		else // ����Ʈ
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
				color = (Color8)(!sortedNodes[playIndex]->gate->preLine[0]->GetColor());
				sortedNodes[playIndex]->gate->SetColor(color);
			}
			else if (sortedNodes[playIndex]->gate->GetID() == typeid(SubGate))
			{
				color = (Color8)(sortedNodes[playIndex]->gate->preLine[0]->GetColor() - sortedNodes[playIndex]->gate->preLine[1]->GetColor());
				sortedNodes[playIndex]->gate->SetColor(color);
			}
		}

		this->playIndex++;

		if (playIndex >= sortedNodes.size())
			tryPlay->Stop();
		}, 0.03f);
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
		if (node->type == 0) // ����Ʈ
		{
			if (node->gate->output.size() != node->gate->nextLine.size()
				|| node->gate->input.size() != node->gate->preLine.size())
			{
				return 1; // ��� ����Ʈ���� ������� ����
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
		else // ����
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