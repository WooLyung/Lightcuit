#pragma once
#include "Gate.h"

class Battery :
	public Gate
{
public:
	Battery(long, long, Dir, Color8);
	~Battery();

	virtual std::type_index GetID(void) { return typeid(Battery); };
};