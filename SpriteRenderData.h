#pragma once
#include "Math.h"
#include "Texture.h"

class SpriteRenderData
{
private:
	Texture* texture;
	Rect visibleArea = { 0, 0, 0, 0 };
	Rect realArea = { 0, 0, 0, 0 };

public:
	SpriteRenderData();
	~SpriteRenderData();

	Texture* GetTexture();
	Rect GetVisibleArea();
	Rect GetRealArea();

	SpriteRenderData* SetTexture(const std::string&);
	SpriteRenderData* SetVisibleArea(Rect);
};