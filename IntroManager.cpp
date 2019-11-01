#include "stdafx.h"
#include "IntroManager.h"
#include "TextRenderer.h"
#include "CommandList.h"
#include "Engine.h"
#include "ChapterScene.h"

IntroManager::IntroManager()
{
}

IntroManager::~IntroManager()
{
}

void IntroManager::OnStart()
{
	AttachComponent<TextRenderer>()
		->SetText("ÀÎÆ®·Î")->SetTextColor(Color(1, 1, 1))->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER);

	CommandList* next = new CommandList;
	next->PushCommand([=]() {
		RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}, 3);
	next->Start();
	commandLists.push_back(next);
}