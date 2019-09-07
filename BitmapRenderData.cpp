#include "stdafx.h"
#include "BitmapRenderData.h"
#include "Engine.h"

BitmapRenderData::BitmapRenderData()
{
}

BitmapRenderData::~BitmapRenderData()
{
}

ID2D1Bitmap1* BitmapRenderData::GetBitmap()
{
	return bitmap;
}

Rect BitmapRenderData::GetVisibleArea()
{
	return visibleArea;
}

BitmapRenderData* BitmapRenderData::SetBitmap(ID2D1Bitmap1* bitmap)
{
	this->bitmap = bitmap;
	
	return this;
}

BitmapRenderData* BitmapRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}