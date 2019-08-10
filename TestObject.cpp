#include "stdafx.h"
#include "TestObject.h"
#include "Effect.h"

TestObject::TestObject(int i)
{
	this->i = i;

	SetName(std::to_string(i) + "N");
	SetTag(std::to_string(i) + "T");

	AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/test.png")
		->SetVisibleArea(Rect(0, 0, 360, 360));

	auto effectInfo = new ColorMatrixEffectInfo();
	effectInfo->SetColor(Color(1, 1, 0, 1));
	AttachComponent<Effect>()
		->PushEffectInfo(effectInfo);

	GetComponent<Transform>()
		->SetAnchor(180, 180)
		->SetScale(0.4f, 0.4f);

	if (i <= 2)
	{
		auto obj1 = new TestObject(i + 1);
		obj1->GetComponent<Transform>()->SetPosX(500);
		auto obj2 = new TestObject(i + 1);
		obj2->GetComponent<Transform>()->SetPosY(500);
		auto obj3 = new TestObject(i + 1);
		obj3->GetComponent<Transform>()->SetPosX(-500);
		auto obj4 = new TestObject(i + 1);
		obj4->GetComponent<Transform>()->SetPosY(-500);

		AttachChild(obj1);
		AttachChild(obj2);
		AttachChild(obj3);
		AttachChild(obj4);
	}
}

TestObject::~TestObject()
{
}