#pragma once
#include "Component.h"
#include "EffectInfo.h"

class EffectInfo;

class Effect :
	public Component
{
private:
	std::vector<EffectInfo* > effects_;

public:
	Effect();
	~Effect();

	std::type_index GetID(void) { return typeid(Effect); }
	static std::type_index GetFamilyID(void) { return typeid(Effect); }

	void Update();
	void Render();
	void Render(ViewRenderer*);

	Effect* PushEffectInfo(EffectInfo* effectInfo);
	Effect* PopEffectInfo();

	std::vector<EffectInfo*>& GetEffects() { return effects_; }

	ID2D1Image* GetOutputImage(ID2D1Image* input);
};