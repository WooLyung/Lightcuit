#include "stdafx.h"
#include "ViewRenderData.h"
#include "Settings.h"

ViewRenderData::ViewRenderData()
{
	size = Size2U(INCH_PER_DISTANCE * 4, INCH_PER_DISTANCE * 4);
}

ViewRenderData::~ViewRenderData()
{
}

ViewRenderData* ViewRenderData::SetCamera(Camera* cam)
{
	targetCamera = cam;

	return this;
}

ViewRenderData* ViewRenderData::SetSize(Size2U size)
{
	this->size = size;

	return this;
}

ViewRenderData* ViewRenderData::SetSizeX(UINT x)
{
	this->size.width = x;

	return this;
}

ViewRenderData* ViewRenderData::SetSizeY(UINT y)
{
	this->size.height = y;

	return this;
}

ViewRenderData* ViewRenderData::SetBackgroundColor(D2D1_COLOR_F color)
{
	backgroundColor = color;

	return this;
}

Camera* ViewRenderData::GetCamera()
{
	return targetCamera;
}

Size2U ViewRenderData::GetSize()
{
	return size;
}

D2D1_COLOR_F ViewRenderData::GetBackgroundColor()
{
	return backgroundColor;
}

ID2D1Bitmap1*& ViewRenderData::GetBitmap()
{
	return bitmap;
}