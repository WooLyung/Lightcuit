#include "stdafx.h"
#include "TextRenderer.h"
#include "Engine.h"

TextRenderer::TextRenderer()
{

}

TextRenderer::~TextRenderer()
{

}

void TextRenderer::Update()
{

}

void TextRenderer::Render()
{
	RG2R_GraphicM->PushRenderBuffer(this);
}

void TextRenderer::Render(ViewRenderData&)
{
	RG2R_GraphicM->PushViewRenderBuffer(this);
}

void TextRenderer::Draw()
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix());
	RG2R_GraphicM->GetDeviceContext()->DrawTextLayout(
		D2D1::Point2F(0, 0),
		defaultData.GetLayout(),
		RG2R_GraphicM->fillBrush_);
}

void TextRenderer::Draw(ViewRenderData& viewRenderData)
{
	RG2R_GraphicM->GetDeviceContext()->SetTransform(GetOwner()->GetAnchorMatrix_v());
	RG2R_GraphicM->GetDeviceContext()->DrawTextLayout(
		D2D1::Point2F(0, 0),
		defaultData.GetLayout(),
		RG2R_GraphicM->fillBrush_);
}

LPCWSTR TextRenderer::GetFontFamily()
{
	return defaultData.GetFontFamily();
}

IDWriteFontCollection* TextRenderer::GetFontCollection()
{
	return defaultData.GetFontCollection();
}

DWRITE_FONT_WEIGHT TextRenderer::GetWeight()
{
	return defaultData.GetWeight();
}

DWRITE_FONT_STYLE TextRenderer::GetStyle()
{
	return defaultData.GetStyle();
}

DWRITE_FONT_STRETCH TextRenderer::GetStretch()
{
	return defaultData.GetStretch();
}

std::string TextRenderer::GetText()
{
	return defaultData.GetText();
}

TextRenderer* TextRenderer::SetFontFamily(LPCWSTR str)
{
	defaultData.SetFontFamily(str);

	return this;
}

TextRenderer* TextRenderer::SetFontCollection(IDWriteFontCollection* collection)
{
	defaultData.SetFontCollection(collection);

	return this;
}

TextRenderer* TextRenderer::SetWeight(DWRITE_FONT_WEIGHT weight)
{
	defaultData.SetWeight(weight);

	return this;
}

TextRenderer* TextRenderer::SetStyle(DWRITE_FONT_STYLE style)
{
	defaultData.SetStyle(style);

	return this;
}

TextRenderer* TextRenderer::SetStretch(DWRITE_FONT_STRETCH stretch)
{
	defaultData.SetStretch(stretch);

	return this;
}

TextRenderer* TextRenderer::SetText(std::string text)
{
	defaultData.SetText(text);

	return this;
}

std::map<Camera*, TextRenderData>* TextRenderer::GetDatas()
{
	return &datas;
}

TextRenderData* TextRenderer::GetDefaultData()
{
	return &defaultData;
}