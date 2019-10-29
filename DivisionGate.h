#pragma once
#include "Gate.h"

class DivisionGate :
	public Gate
{
public:
	DivisionGate(long, long);
	~DivisionGate();

	virtual std::type_index GetID(void) { return typeid(DivisionGate); };
};