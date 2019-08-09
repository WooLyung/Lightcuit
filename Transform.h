#pragma once
#include "Component.h"
class Transform :
	public Component
{
private:
	Vec2F pos = { 0, 0 };
	Vec2F scale = { 1, 1 };
	float rot = 0;

	Vec2F center = { 0, 0 };
	Vec2F anchor_scale = { 0, 0 };
	Vec2F anchor_rot = { 0, 0 };

	bool isRelative = true;

public:
	Transform();
	~Transform();

	std::type_index GetID(void) { return typeid(Transform); }
	static std::type_index GetFamilyID(void) { return typeid(Transform); }

	void Update();
	void Render();

	Vec2F GetPos();
	Vec2F GetScale();
	float GetRot();
	Vec2F GetCenter();
	Vec2F GetAnchor_scale();
	Vec2F GetAnchor_rot();
	void SetPos(Vec2F);
	void SetScale(Vec2F);
	void SetRot(float);
	void SetPosX(float);
	void SetPosY(float);
	void SetScaleX(float);
	void SetScaleY(float);
	void SetCenter(Vec2F);
	void SetAnchor_scale(Vec2F);
	void SetAnchor_rot(Vec2F);
	void SetCenterX(float);
	void SetCenterY(float);
	void SetAnchor_scaleX(float);
	void SetAnchor_scaleY(float);
	void SetAnchor_rotX(float);
	void SetAnchor_rotY(float);
	bool GetIsRelative();
	void SetIsRelative(bool);
};