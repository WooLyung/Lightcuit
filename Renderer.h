#pragma once
#include "Component.h"
class Renderer :
	public Component
{
public:
	Renderer();
	~Renderer();

	virtual std::type_index GetID(void) override = 0 { return typeid(Renderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	virtual void Update() = 0;
	virtual void Render() = 0;
};