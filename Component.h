#pragma once
class Component
{
public:
	Component();
	~Component();

	static std::type_index GetFamilyID(void) { return typeid(Component); }
};