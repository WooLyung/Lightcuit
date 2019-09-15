#include "stdafx.h"
#include "TestObject.h"
#include "Effect.h"
#include "TextRenderer.h"
#include "AnimationRenderer.h"
#include "Textures.h"

TestObject::TestObject(int i)
{
	this->i = i;

	SetName(std::to_string(i) + "N");
	SetTag(std::to_string(i) + "T");

	Textures textures1;
	textures1.PushTexture("Resources/Sprites/spr1.png")
		->PushTexture("Resources/Sprites/spr2.png")
		->PushTexture("Resources/Sprites/spr3.png")
		->PushTexture("Resources/Sprites/spr4.png");

	auto animationRenderer = AttachComponent<AnimationRenderer>();
	animationRenderer
		->GetAnimations()
		->push_back(textures1);
	animationRenderer
		->SetVisibleArea()
		->SetInterval(0.5f);

	//auto effectInfo = new ColorMatrixEffectInfo();
	//effectInfo->SetColor(Color(0.2f * i + 0.4f, 0.1f * i, 0.9f - i * 0.1f, 1));
	//AttachComponent<Effect>()
	//	->PushEffectInfo(effectInfo);

	GetComponent<Transform>()
		->SetAnchor(16, 16)
		->SetScale(0.4f, 0.4f);

	if (i <= 2)
	{
		auto obj1 = new TestObject(i + 1);
		obj1->GetComponent<Transform>()->SetPosX(3);
		auto obj2 = new TestObject(i + 1);
		obj2->GetComponent<Transform>()->SetPosY(3);
		auto obj3 = new TestObject(i + 1);
		obj3->GetComponent<Transform>()->SetPosX(-3);
		auto obj4 = new TestObject(i + 1);
		obj4->GetComponent<Transform>()->SetPosY(-3);

		AttachChild(obj1);
		AttachChild(obj2);
		AttachChild(obj3);
		AttachChild(obj4);
	}
}

TestObject::~TestObject()
{
}