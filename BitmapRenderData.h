#pragma once
#include "Math.h"
#include "Texture.h"

class BitmapRenderData
{
private:
	ID2D1Bitmap1* bitmap;
	Rect visibleArea = { 0, 0, 0, 0 };

public:
	BitmapRenderData();
	~BitmapRenderData();

	ID2D1Bitmap1* GetBitmap();
	Rect GetVisibleArea();

	BitmapRenderData* SetBitmap(ID2D1Bitmap1*);
	BitmapRenderData* SetVisibleArea(Rect);
};