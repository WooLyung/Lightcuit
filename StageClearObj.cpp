#include "stdafx.h"
#include "StageClearObj.h"

StageClearObj::StageClearObj()
{
}

StageClearObj::~StageClearObj()
{
}

void StageClearObj::OnStart()
{
	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/UIs/white.png");
	spriteRenderer->SetZ_index(1000);
	transform = GetComponent<Transform>()
		->SetAnchor(256, 128)
		->SetIsRelative(false);
}

void StageClearObj::OnUpdate()
{

}