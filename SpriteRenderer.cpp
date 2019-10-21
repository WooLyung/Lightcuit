#include "stdafx.h"
#include "SpriteRenderer.h"
#include "Engine.h"
#include "Transform.h"
#include "SpriteRenderData.h"
#include "ViewRenderData.h"
#include "Effect.h"
#include "Camera.h"
#include <map>

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

void SpriteRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void SpriteRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (effect != nullptr)
	{
		ID2D1Image* image = effect->GetOutputImage(defaultData.GetTexture()->GetBitmap());

		RG2R_GraphicM->GetDeviceContext()->DrawImage(
			image,
			nullptr,
			&defaultData.GetVisibleArea(),
			D2D1_INTERPOLATION_MODE_LINEAR,
			D2D1_COMPOSITE_MODE_SOURCE_OVER);
	}
	else
	{
		RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
			defaultData.GetTexture()->GetBitmap(),
			nullptr,
			1.f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
			&defaultData.GetVisibleArea());
	}
}

void SpriteRenderer::Draw(ViewRenderData& viewRenderData)
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix_v());

	Effect* effect = GetOwner()->GetComponent<Effect>();

	if (datas.find(viewRenderData.GetCamera()) != datas.end())
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(datas[viewRenderData.GetCamera()].GetTexture()->GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&datas[viewRenderData.GetCamera()].GetVisibleArea(),
				D2D1_INTERPOLATION_MODE_LINEAR,
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
				datas[viewRenderData.GetCamera()].GetTexture()->GetBitmap(),
				nullptr,
				1.f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				&datas[viewRenderData.GetCamera()].GetVisibleArea());
		}
	}
	else
	{
		if (effect != nullptr)
		{
			ID2D1Image* image = effect->GetOutputImage(defaultData.GetTexture()->GetBitmap());

			RG2R_GraphicM->GetDeviceContext()->DrawImage(
				image,
				nullptr,
				&defaultData.GetVisibleArea(),
				D2D1_INTERPOLATION_MODE_LINEAR,
				D2D1_COMPOSITE_MODE_SOURCE_OVER);
		}
		else
		{
			RG2R_GraphicM->GetDeviceContext()->DrawBitmap(
				defaultData.GetTexture()->GetBitmap(),
				nullptr,
				1.f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				&defaultData.GetVisibleArea());
		}
	}
}

std::map<Camera*, SpriteRenderData>* SpriteRenderer::GetDatas()
{
	return &datas;
}

SpriteRenderData* SpriteRenderer::GetDefaultData()
{
	return &defaultData;
}

Texture* SpriteRenderer::GetTexture()
{
	return defaultData.GetTexture();
}

Rect SpriteRenderer::GetVisibleArea()
{
	return defaultData.GetVisibleArea();
}

Rect SpriteRenderer::GetRealArea()
{
	return defaultData.GetRealArea();
}

SpriteRenderer* SpriteRenderer::SetTexture(const std::string& str)
{
	defaultData.SetTexture(str);

	return this;
}

SpriteRenderer* SpriteRenderer::SetVisibleArea(Rect rect)
{
	defaultData.SetVisibleArea(rect);

	return this;
}

SpriteRenderer* SpriteRenderer::SetVisibleArea(float a, float b, float c, float d)
{
	defaultData.SetVisibleArea(a, b, c, d);

	return this;
}