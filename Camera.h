#pragma once
#include "Scene.h"
#include "Math.h"

class Scene;

class Camera
{
private:
	Scene* scene = nullptr;
	std::string name = "";
	bool isMain = false;
	bool isFlipX = false;
	bool isFlipY = false;

	Vec2F pos = { 0, 0 };
	Vec2F zoom = { 1, 1 };
	float rot = 0;

	void Update();

	friend class Scene;

public:
	Camera();
	~Camera();

	std::string GetName(); // 이름 얻기
	Scene* GetScene(); // 씬 얻기

	Vec2F GetPos();
	Vec2F GetZoom();
	float GetRot();
	Size2F GetCameraSize();
	Size2F GetCameraDefaultSize();

	void SetPos(Vec2F);
	void SetZoom(Vec2F);
	void SetRot(float);
	void SetPosX(float);
	void SetPosY(float);
	void SetZoomX(float);
	void SetZoomY(float);
	void SetIsFlipX(bool);
	void SetIsFlipY(bool);

	bool GetIsMain() { return isMain; }
	bool GetIsFlipX() { return isFlipX; }
	bool GetIsFlipY() { return isFlipY; }
};