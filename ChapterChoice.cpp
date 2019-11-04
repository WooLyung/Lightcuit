#include "stdafx.h"
#include "ChapterChoice.h"
#include "Engine.h"
#include "TextRenderer.h"
#include "StageScene.h"
#include "StageData.h"

ChapterChoice::ChapterChoice(int chapter, std::string path)
{
	this->chapter = chapter;
	this->path = path;
}

ChapterChoice::~ChapterChoice()
{
}

void ChapterChoice::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture(path)
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	transform = GetComponent<Transform>()
		->SetScale(0.4f, 0.4f)
		->SetPos(3.5f * (chapter - 2), -5)
		->SetAnchor(spriteRenderer->GetTexture()->GetSize().width * 0.5f, spriteRenderer->GetTexture()->GetSize().height * 0.5f);

	appearAnim = new CommandList;
	commandLists.push_back(appearAnim);
	appearAnim->PushCommand([=]() {
		animTime += RG2R_TimeM->GetDeltaTime();
		transform->SetPosY(-pow(animTime - 1, 2) * 5);
		transform->SetRot(-(pow(animTime - 1, 2) + 1) * 20);

		if (animTime >= 1)
		{
			transform->SetPosY(0);
			animTime = 0;
			appearAnim->Stop();
			state = ChapterState::wait;
		}
		}, 0);
	appearAnim->SetIsLoop(true);
}

void ChapterChoice::OnUpdate()
{
	if (ChapterChoice::state == ChapterState::appear)
	{
		animTime += RG2R_TimeM->GetDeltaTime();
		if (animTime >= 0.2f * chapter)
		{
			state = ChapterState::wait;
			animTime = 0;
			appearAnim->Start();
		}
	}

	if (RG2R_InputM->GetMouseState(MouseCode::MOUSE_LBUTTON) == KeyState::KEYSTATE_ENTER)
	{
		Vec2F vec = RG2R_InputM->GetMouseWorldPos() - transform->GetPos();

		if (vec.Dot(vec) <= 4)
		{
			StageData::GetInstance()->chapter = chapter;
			std::cout << "chapter : " << chapter << endl;

			//RG2R_SceneM->ChangeScene(new StageScene, true);
		}
	}
}

Transform* ChapterChoice::GetTransform()
{
	return transform;
}

SpriteRenderer* ChapterChoice::GetSpriteRenderer()
{
	return spriteRenderer;
}