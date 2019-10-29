#pragma once
#include "Object.h"
#include "Transform.h"

class ColorSet :
	public Object
{
private:
	Object *red, *green, *blue;
	Transform* transform;

public:
	ColorSet();
	~ColorSet();

	void OnStart();

	void SetPos(float, float);
	Color8 GetColor();
};