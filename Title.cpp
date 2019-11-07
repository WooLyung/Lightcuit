#include "stdafx.h"
#include "Title.h"
#include "Engine.h"
#include "ChapterScene.h"

Title::Title()
{
	transform = GetComponent<Transform>();
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/Chapters/chapterLock.png");

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);
		transform->SetRot(-(pow(animTime - 1, 2) + 1) * 20);

		if (animTime >= 1)
		{
			transform->SetPosY(0);
			animTime = 1;
			appearAnim->Stop();
		}
		}, 0);
	appearAnim->SetIsLoop(true);
	appearAnim->Start();

	disappearAnim = new CommandList;
	commandLists.push_back(disappearAnim);
	disappearAnim->PushCommand([=]() {
		animTime -= RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);
		transform->SetRot(-(pow(animTime - 1, 2) + 1) * 20);

		if (animTime <= 0)
		{
			RG2R_SceneM->ChangeScene(new ChapterScene, true);
		}
		}, 0);
	disappearAnim->SetIsLoop(true);
}

Title::~Title()
{
}

void Title::NextScene()
{
	disappearAnim->Start();
}