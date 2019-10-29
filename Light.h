#pragma once
#include "Gate.h"

class Light :
	public Gate
{
public:
	Light(long, long);
	~Light();

	virtual std::type_index GetID(void) { return typeid(Light); };
};