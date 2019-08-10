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
	}

	void OnUpdate()
	{
		GetComponent<Transform>()->SetRot(
			GetComponent<Transform>()->GetRot() + RG2R_TimeM->GetDeltaTime() * 18
		);
	}
};

