#include "stdafx.h"
#include "SpriteRenderData.h"
#include "Engine.h"

SpriteRenderData::SpriteRenderData()
{
}

SpriteRenderData::~SpriteRenderData()
{
}

Texture* SpriteRenderData::GetTexture()
{
	return texture;
}

Rect SpriteRenderData::GetVisibleArea()
{
	return visibleArea;
}

Rect SpriteRenderData::GetRealArea()
{
	return realArea;
}

SpriteRenderData* SpriteRenderData::SetTexture(const std::string& path)
{
	texture = RG2R_TextureM->Load(path);
	visibleArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);
	realArea = Rect(0.f, 0.f, texture->GetSize().width, texture->GetSize().height);

	return this;
}

SpriteRenderData* SpriteRenderData::SetVisibleArea(Rect rect)
{
	visibleArea = rect;

	return this;
}