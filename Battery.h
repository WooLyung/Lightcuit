#pragma once
#include "Gate.h"

class Battery :
	public Gate
{
public:
	Battery(long, long);
	~Battery();
};