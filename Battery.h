#pragma once
#include "Gate.h"

class Battery :
	public Gate
{
public:
	Battery(long, long);
	~Battery();

	virtual std::type_index GetID(void) { return typeid(Battery); };
};