#include "stdafx.h"
#include "PlayManager.h"
#include "Engine.h"
#include "Battery.h"
#include <stack>

PlayManager::PlayManager(InGameScene* scene)
{
	this->scene = scene;
}

PlayManager::~PlayManager()
{
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

void PlayManager::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_F) == KeyState::KEYSTATE_ENTER)
		CheckClear();
}