#include "stdafx.h"
#include "Line.h"
#include "SpriteRenderer.h"

Line::Line(long x, long y)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>()
		->SetTexture("Resources/Sprites/Lines/line1.png")
		->SetEnlargementType(EnlargementType::HIGH_QUALITY_CUBIC);
	effect = AttachComponent<Effect>();
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);
}

Line::~Line()
{
}

void Line::OnStart()
{
	changeColor = new CommandList;
	changeColor->PushCommand([=]() {
		if (nowColor.r == toColor.r && nowColor.g == toColor.g && nowColor.b == toColor.b && nowColor.a == toColor.a)
		{
			changeColor->Stop();
		}
		else
		{
			if (nowColor.r > toColor.r)
			{
				nowColor.r -= 0.04f;
				if (nowColor.r <= toColor.r)
				{
					nowColor.r = toColor.r;
				}
			}
			else if (nowColor.r < toColor.r)
			{
				nowColor.r += 0.04f;
				if (nowColor.r >= toColor.r)
				{
					nowColor.r = toColor.r;
				}
			}
			if (nowColor.b > toColor.b)
			{
				nowColor.b -= 0.04f;
				if (nowColor.b <= toColor.b)
				{
					nowColor.b = toColor.b;
				}
			}
			else if (nowColor.b < toColor.b)
			{
				nowColor.b += 0.04f;
				if (nowColor.b >= toColor.b)
				{
					nowColor.b = toColor.b;
				}
			}
			if (nowColor.g > toColor.g)
			{
				nowColor.g -= 0.04f;
				if (nowColor.g <= toColor.g)
				{
					nowColor.g = toColor.g;
				}
			}
			else if (nowColor.g < toColor.g)
			{
				nowColor.g += 0.04f;
				if (nowColor.g >= toColor.g)
				{
					nowColor.g = toColor.g;
				}
			}
			if (nowColor.a > toColor.a)
			{
				nowColor.a -= 0.04f;
				if (nowColor.a <= toColor.a)
				{
					nowColor.a = toColor.a;
				}
			}
			else if (nowColor.a < toColor.a)
			{
				nowColor.a += 0.04f;
				if (nowColor.a >= toColor.a)
				{
					nowColor.a = toColor.a;
				}
			}

			effect->ClearEffectInfo()
				->PushEffectInfo(new ColorMatrixEffectInfo(nowColor));
		}
		}, 0.01f);
	changeColor->SetIsLoop(true);

	commandLists.push_back(changeColor);
}

Transform* Line::GetTransform()
{
	return transform;
}

SpriteRenderer* Line::GetSpriteRenderer()
{
	return spriteRenderer;
}


void Line::SetColor(Color8 newColor)
{
	color = newColor;	
	toColor = Color(color.r, color.g, color.b, 1);
	changeColor->Start();
}