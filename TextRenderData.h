#pragma once
#include "Math.h"
#include <string>

class TextRenderData
{
private:
	IDWriteTextFormat* format;
	IDWriteTextLayout* layout;

	LPCWSTR fontFamily;
	IDWriteFontCollection* fontCollection;
	DWRITE_FONT_WEIGHT weight;
	DWRITE_FONT_STYLE style;
	DWRITE_FONT_STRETCH stretch;
	std::string text;
	float size;

public:
	TextRenderData();
	~TextRenderData();

	LPCWSTR GetFontFamily();
	IDWriteFontCollection* GetFontCollection();
	DWRITE_FONT_WEIGHT GetWeight();
	DWRITE_FONT_STYLE GetStyle();
	DWRITE_FONT_STRETCH GetStretch();
	std::string GetText();
	IDWriteTextFormat*& GetFormat();
	IDWriteTextLayout*& GetLayout();

	TextRenderData* SetFontFamily(LPCWSTR);
	TextRenderData* SetFontCollection(IDWriteFontCollection*);
	TextRenderData* SetWeight(DWRITE_FONT_WEIGHT);
	TextRenderData* SetStyle(DWRITE_FONT_STYLE);
	TextRenderData* SetStretch(DWRITE_FONT_STRETCH);
	TextRenderData* SetText(std::string);
};