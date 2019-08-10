#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Transform.h"

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
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());
	RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
		texture->GetBitmap(),
		nullptr,
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		&GetVisibleArea());
}

void SpriteRenderer::Draw()
{

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

SpriteRenderer* SpriteRenderer::SetZ_index(float index)
{
	this->z_index = index;

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

float SpriteRenderer::GetZ_index()
{
	return z_index;
}