#include "stdafx.h"
#include "Scene1.h"
#include "TextRenderer.h"
#include "Engine.h"
#include "Scene2.h"
#include <iostream>

Scene2::Scene2()
{
	CreateObject()
		->AttachComponent<TextRenderer>()
		->SetAlignmentHeight(TextAlignment::ALIGN_CENTER)
		->SetAlignmentWidth(TextAlignment::ALIGN_CENTER)
		->SetText("¹«·Á µÎ¹øÂ° ¾À!")
		->SetTextColor(Color(1, 1, 1))
		->SetSize(30);
}

Scene2::~Scene2()
{
	std::cout << "¾À2 »èÁ¦µÊ" << std::endl;
}

void Scene2::OnDestroy()
{
	std::cout << "¾À2 »èÁ¦µÊ" << std::endl;
}

void Scene2::OnUpdate()
{
	if (RG2R_InputM->GetKeyState(KeyCode::KEY_W) == KeyState::KEYSTATE_ENTER)
	{
		RG2R_SceneM->ChangeScene(new Scene1, true);
	}
}