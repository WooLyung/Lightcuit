#include "stdafx.h"
#include "Gate.h"
#include "CommandList.h"
#include "Command.h"

Gate::Gate(long x, long y)
{
	tilePos = Vec2L(x, y);

	spriteRenderer = AttachComponent<SpriteRenderer>();
	effect = AttachComponent<Effect>();
	transform = GetComponent<Transform>()
		->SetAnchor(64, 64)
		->SetPos(x, y);

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

Gate::~Gate()
{
}

Dir Gate::GetDir()
{
	return dir;
}

void Gate::SetColor(Color8 newColor)
{
	color = newColor;

	switch (color)
	{
		case Color8::R:
			toColor = Color(1, 0, 0, 1);
			break;
		case Color8::G:
			toColor = Color(0, 1, 0, 1);
			break;
		case Color8::B:
			toColor = Color(0, 0, 1, 1);
			break;
		case Color8::C:
			toColor = Color(0, 1, 1, 1);
			break;
		case Color8::M:
			toColor = Color(1, 0, 1, 1);
			break;
		case Color8::Y:
			toColor = Color(1, 1, 0, 1);
			break;
		case Color8::K:
			toColor = Color(0, 0, 0, 1);
			break;
		case Color8::W:
			toColor = Color(1, 1, 1, 1);
			break;
	}

	changeColor->Start();
}

void Gate::SetDir(Dir dir)
{
	this->dir = dir;

	switch (dir)
	{
		case Dir::RIGHT:
			transform->SetRot(0);
			break;
		case Dir::DOWN:
			transform->SetRot(90);
			break;
		case Dir::LEFT:
			transform->SetRot(180);
			break;
		case Dir::UP:
			transform->SetRot(270);
			break;
	}
}

Transform* Gate::GetTransform()
{
	return transform;
}

SpriteRenderer* Gate::GetSpriteRenderer()
{
	return spriteRenderer;
}

void Gate::SetPos(int x, int y)
{
	transform->SetPos(x, y);
	tilePos = Vec2L(x, y);
}