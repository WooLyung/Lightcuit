#include "stdafx.h"
#include "TextRenderData.h"
#include "Engine.h"
#include <string>

TextRenderData::TextRenderData()
{
	size = 50;
	text = "히히히히히";

	RG2R_GraphicM->GetDwFactory()->CreateTextFormat(
		Widen("궁서").c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		size,
		L"ko",
		&format
	);

	RG2R_GraphicM->GetDwFactory()->CreateTextLayout(
		Widen(text).c_str(),
		Widen(text).length(),
		format,
		RG2R_GraphicM->GetDeviceContext()->GetSize().width,
		RG2R_GraphicM->GetDeviceContext()->GetSize().height,
		&layout);
}

TextRenderData::~TextRenderData()
{

}

LPCWSTR TextRenderData::GetFontFamily()
{
	return fontFamily;
}

IDWriteFontCollection* TextRenderData::GetFontCollection()
{
	return fontCollection;
}

DWRITE_FONT_WEIGHT TextRenderData::GetWeight()
{
	return weight;
}

DWRITE_FONT_STYLE TextRenderData::GetStyle()
{
	return style;
}

DWRITE_FONT_STRETCH TextRenderData::GetStretch()
{
	return stretch;
}

string TextRenderData::GetText()
{
	return text;
}

IDWriteTextFormat*& TextRenderData::GetFormat()
{
	return format;
}

IDWriteTextLayout*& TextRenderData::GetLayout()
{
	return layout;
}

TextRenderData* TextRenderData::SetText(string text)
{
	this->text = text;

	if (layout != nullptr)
		layout->Release();
	RG2R_GraphicM->GetDwFactory()->CreateTextLayout(
		Widen(text).c_str(),
		Widen(text).length(),
		format,
		RG2R_GraphicM->GetDeviceContext()->GetSize().width,
		RG2R_GraphicM->GetDeviceContext()->GetSize().height,
		&layout);

	return this;
}

TextRenderData* TextRenderData::SetFontFamily(LPCWSTR)
{
	return this;
}

TextRenderData* TextRenderData::SetFontCollection(IDWriteFontCollection*) 
{
	return this;
}

TextRenderData* TextRenderData::SetWeight(DWRITE_FONT_WEIGHT)
{
	return this;
}

TextRenderData* TextRenderData::SetStyle(DWRITE_FONT_STYLE)
{
	return this;
}

TextRenderData* TextRenderData::SetStretch(DWRITE_FONT_STRETCH)
{
	return this;
}