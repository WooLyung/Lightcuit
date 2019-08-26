#include "stdafx.h"
#include "ViewRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

ViewRenderer::ViewRenderer()
{
	backgroundColor = D2D1::ColorF(BACKGROUND_COLOR);

	const D2D1_BITMAP_PROPERTIES1 bitmapProperties =
		D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE),
			96.f,
			96.f
		);

	RG2R_GraphicM->GetDeviceContext()->CreateBitmap(
		size,
		nullptr,
		0,
		&bitmapProperties,
		&bitmap
	);
}

ViewRenderer::~ViewRenderer()
{
}

void ViewRenderer::Update()
{

}

void ViewRenderer::Render(ViewRenderer*)
{

}

void ViewRenderer::Render()
{
	// 내장 비트맵에 출력
	RG2R_GraphicM->GetViewRenderBuffer()->clear();
	RG2R_SceneM->Render(this);

	RG2R_GraphicM->SetTargetBitmap(bitmap);
	RG2R_GraphicM->GetDeviceContext()->BeginDraw();
	RG2R_GraphicM->GetDeviceContext()->Clear(backgroundColor);

	sort(RG2R_GraphicM->GetViewRenderBuffer()->begin(), RG2R_GraphicM->GetViewRenderBuffer()->end(), [](Renderer* renderer1, Renderer* renderer2) -> bool {
		return renderer1->GetZ_index() > renderer2->GetZ_index();
		});
	for_each(RG2R_GraphicM->GetViewRenderBuffer()->begin(), RG2R_GraphicM->GetViewRenderBuffer()->end(), [](Renderer* renderer) -> void {
		renderer->Draw();
		});

	RG2R_GraphicM->GetDeviceContext()->EndDraw();

	// 실제 출력
	RG2R_GraphicM->PushRenderBuffer(this);
}

void ViewRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(bitmap);

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&Rect(0, 0, size.width, size.height),
			D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
			bitmap,
			nullptr,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			&Rect(0, 0, size.width, size.height));
	}
}

void ViewRenderer::Draw(ViewRenderer*)
{

}

ViewRenderer* ViewRenderer::SetCamera(Camera* camera)
{
	targetCamera = camera;

	return this;
}

ViewRenderer* ViewRenderer::SetSize(Size2U size)
{
	this->size = size;

	return this;
}

ViewRenderer* ViewRenderer::SetSizeX(UINT x)
{
	this->size.width = x;

	return this;
}

ViewRenderer* ViewRenderer::SetSizeY(UINT y)
{
	this->size.height = y;

	return this;
}

ViewRenderer* ViewRenderer::SetBackgroundColor(D2D1_COLOR_F color)
{
	this->backgroundColor = color;

	return this;
}

Camera* ViewRenderer::GetCamera()
{
	return targetCamera;
}

Size2U ViewRenderer::GetSize()
{
	return size;
}

D2D1_COLOR_F ViewRenderer::GetBackgroundColor()
{
	return backgroundColor;
}