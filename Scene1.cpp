#include "stdafx.h"
#include "Scene1.h"
#include "AnimationRenderer.h"
#include "Engine.h"
#include "Scene2.h"
#include <iostream>
#include "SpriteRenderer.h"
#include "Textures.h"
#include "Transform.h"

Scene1::Scene1()
{
	Textures textures1;
	textures1.PushTexture("Resources/Sprites/1.png")
		->PushTexture("Resources/Sprites/2.png")
		->PushTexture("Resources/Sprites/3.png")
		->PushTexture("Resources/Sprites/4.png");
	Textures textures2;
	textures2.PushTexture("Resources/Sprites/1.png")
		->PushTexture("Resources/Sprites/2.png");

	auto anim = CreateObject()
		->AttachComponent<AnimationRenderer>();

	anim->GetAnimations()->push_back(textures1);
	anim->GetAnimations()->push_back(textures2);
	anim->SetVisibleArea();
	anim->SetTargetAnim(1);

	GetMainCamera()->SetRot(50)
		->Translate(3, 1)
		->SetZoom(0.5f, 0.5f);
}

Scene1::~Scene1()
{
	std::cout << "¾À1 »èÁ¦µÊ" << std::endl;
}

void Scene1::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER)
	{
		CreateObject()
			->AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/1.png")
			->GetOwner()
			->GetComponent<Transform>()
			->SetPos(RG2R_InputM->FromUIToWorld(RG2R_InputM->FromWorldToUI(RG2R_InputM->FromUIToWorld(RG2R_InputM->GetMousePos()))));
	}
}