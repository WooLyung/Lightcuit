#pragma once
#include "Object.h"
#include "Transform.h"
#include "SpriteRenderer.h"
#include "Engine.h"

class TestObject :
	public Object
{
public:
	int i = 0;

	TestObject(int i);
	~TestObject();

	void OnStart()
	{
		AttachComponent<SpriteRenderer>()
			->SetTexture("Resources/Sprites/test.png");
		GetComponent<Transform>()
			->SetAnchor(180, 180)
			->SetScale(0.4f, 0.4f);

		if (i <= 3)
		{
			auto obj1 = new TestObject(i+1);
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

	void OnUpdate()
	{
		GetComponent<Transform>()->SetRot(
			GetComponent<Transform>()->GetRot() + RG2R_TimeM->GetDeltaTime() * 18
		);
	}
};

