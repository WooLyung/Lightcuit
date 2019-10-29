#pragma once
#include "Gate.h"

class SubGate :
	public Gate
{
public:
	SubGate(long, long);
	~SubGate();

	virtual std::type_index GetID(void) { return typeid(SubGate); };
};