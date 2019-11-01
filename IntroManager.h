#pragma once
#include "Object.h"

class IntroManager :
	public Object
{
public:
	IntroManager();
	~IntroManager();

	void OnStart();
};