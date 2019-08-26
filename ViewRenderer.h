#pragma once
#include "Renderer.h"
#include "Camera.h"
#include "Settings.h"

class ViewRenderer :
	public Renderer
{
private:
	Camera* targetCamera;
	ID2D1Bitmap1* bitmap;
	Size2U size;
	D2D1_COLOR_F backgroundColor;

public:
	ViewRenderer();
	~ViewRenderer();

	std::type_index GetID(void) override { return typeid(ViewRenderer); }
	static std::type_index GetFamilyID(void) { return typeid(Renderer); }

	void Update();
	void Render();
	void Draw();

	ViewRenderer* SetCamera(Camera*);
	ViewRenderer* SetSize(Size2U);
	ViewRenderer* SetSizeX(UINT);
	ViewRenderer* SetSizeY(UINT);
	ViewRenderer* SetBackgroundColor(D2D1_COLOR_F);
	Camera* GetCamera();
	Size2U GetSize();
	D2D1_COLOR_F GetBackgroundColor();
};