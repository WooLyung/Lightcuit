#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "Effect.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
}

void SpriteRenderer::Update()
{

}

void SpriteRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void SpriteRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(texture->GetBitmap());

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&GetVisibleArea(),
			D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
			texture->GetBitmap(),
			nullptr,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			&GetVisibleArea());
	}
}

SpriteRenderer* SpriteRenderer::SetTexture(const std::string& path)
{
	texture = RG2R_TextureM->Load(path);
	visibleArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);
	realArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);

	return this;
}

SpriteRenderer* SpriteRenderer::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}

Texture* SpriteRenderer::GetTexture()
{
	return texture;
}

Rect SpriteRenderer::GetVisibleArea()
{
	return visibleArea;
}

Rect SpriteRenderer::GetRealArea()
{
	return realArea;
}